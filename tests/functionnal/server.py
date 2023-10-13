import os
import sys
import subprocess
import time
import socket
import struct
import threading

import pack

from abc import ABC, abstractmethod
from typing import List, Tuple, Any, Dict

SERVER_BINARY: str = './r-type_server'
if sys.platform == 'win32':
    SERVER_BINARY = SERVER_BINARY + '.exe'
SERVER_PORT: int = 12345


class Test(ABC):
    TESTS = []

    def __init_subclass__(cls, **kwargs):
        cls.TESTS.append(cls)

    def __init__(self):
        self._server_process: subprocess.Popen = None
        self._sock: socket.socket = None

    def start_server(self):
        self._server_process: subprocess.Popen = subprocess.Popen([SERVER_BINARY],
                                                                     stdout=subprocess.PIPE,
                                                                     stderr=subprocess.PIPE)
        time.sleep(0.6)

    def connect(self):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.connect(('localhost', SERVER_PORT))

    def stop_server(self):
        if sys.platform == 'linux':
            for _ in range(3):
                try:
                    self._server_process.send_signal(subprocess.signal.SIGINT)
                    self._server_process.send_signal(subprocess.signal.SIGTERM)
                    self._server_process.kill()
                except:
                    time.sleep(0.1)
        else:
            self._server_process.kill()

    @abstractmethod
    def run_tests(self):
        pass

    def check_exit_code(self):
        if self._server_process.returncode is not None:
            if self._server_process.returncode == 0:
                raise RuntimeError('Server exited with code 0, should not be closed')
            raise RuntimeError(f'Server exited with code {self._server_process.returncode} (crashed)')

    def check_outputs(self):
        stderr = self._server_process.stderr.read()
        if b'terminate called after throwing' in stderr:
            print("====================================")
            print(stderr)
            print("====================================")
            raise RuntimeError('Server crashed (CPP unhandled exception)')

    def run(self):
        self.start_server()
        self.connect()
        try:
            self.run_tests()
        except Exception as e:
            pass
        finally:
            self.stop_server()
            self.check_exit_code()
            self.check_outputs()
    
    @classmethod
    def run_all_tests(cls) -> Tuple[int, int]:
        passes, fails = 0, 0
        for test in cls.TESTS:
            print(f'Running test {test.__name__}...')
            try:
                test().run()
                passes += 1
                print(f'Passed')
            except Exception as e:
                fails += 1
                print(f'Failed: {e}')
            if test is not cls.TESTS[-1]:
                time.sleep(2)
            
        return passes, fails


class TestConnect(Test):
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.ConnectAck, data)
        assert unpacked[0] == pack.HEADER_MAGIC
        assert unpacked[1] == pack.Server.ConnectAck
        assert unpacked[-1] == pack.FOOTER_MAGIC


class TestCreateRoom(Test):
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.CreateRoom))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.RoomInformation, data)
        assert unpacked[0] == pack.HEADER_MAGIC
        assert unpacked[1] == pack.Server.ConnectAck
        assert unpacked[-1] == pack.FOOTER_MAGIC

    
class TestChooseLevel(Test):
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.ChooseLevel, 0))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.LevelInformation, data)
        assert unpacked[0] == pack.HEADER_MAGIC
        assert unpacked[1] == pack.Server.LevelInformation
        assert unpacked[-1] == pack.FOOTER_MAGIC



class TestWholeStartSequence(Test):
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.ConnectAck, data)
        assert unpacked[1] == pack.Server.ConnectAck

        self._sock.send(pack.Client.pack(pack.Client.CreateRoom))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.RoomInformation, data)
        assert unpacked[1] == pack.Server.RoomInformation

        self._sock.send(pack.Client.pack(pack.Client.ChooseLevel, 0))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.LevelInformation, data)
        assert unpacked[1] == pack.Server.LevelInformation

        self._sock.send(pack.Client.pack(pack.Client.StartGame))
        data = self._sock.recv(1024)
        unpacked = pack.Server.unpack(pack.Server.GameStarted, data)
        assert unpacked[1] == pack.Server.GameStarted


class TestCrashCheck1(Test):
    # Just send a movement packet with an initialized client to check that it doesn't crash
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.PlayerMovement, 0, 0, 0, 0, 1, 0))


class TestCrashCheck2(Test):
    # Send one movement packet after the connect sequence
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        self._sock.send(pack.Client.pack(pack.Client.CreateRoom))
        self._sock.send(pack.Client.pack(pack.Client.ChooseLevel, 0))
        self._sock.send(pack.Client.pack(pack.Client.StartGame))
        self._sock.send(pack.Client.pack(pack.Client.PlayerMovement, 0, 0, 0, 0, 1, 0))


class TestCrashCheck3(Test):
    # Send one movement packet after half finished start
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        self._sock.send(pack.Client.pack(pack.Client.PlayerMovement, 0, 0, 0, 0, 1, 0))


class TestCrashCheck4(Test):
    # Send one movement packet without starting game
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        self._sock.send(pack.Client.pack(pack.Client.CreateRoom))
        self._sock.send(pack.Client.pack(pack.Client.ChooseLevel, 0))
        self._sock.send(pack.Client.pack(pack.Client.PlayerMovement, 0, 0, 0, 0, 1, 0))


class TestCrashCheck5(Test):
    # Send one player shoot without real game
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Connect))
        self._sock.send(pack.Client.pack(pack.Client.PlayerShoot))


class TestRandomMessages1(Test):
    # Send messages in some random orders
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.Ack))
        self._sock.send(pack.Client.pack(pack.Client.StartGame))


class TestRandomMessages2(Test):
    # Send messages in some random orders
    def run_tests(self):
        self._sock.send(pack.Client.pack(pack.Client.ChooseRoom))
        self._sock.send(pack.Client.pack(pack.Client.ChooseRoom))
        self._sock.send(pack.Client.pack(pack.Client.ChooseRoom))


if __name__ == '__main__':
    print("Starting functionnal tests for the server")
    print()
    passes, fails = Test.run_all_tests()
    print()
    print(f'Passed: {passes}, Failed: {fails}')
