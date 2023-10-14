import struct

from typing import Dict, List, Tuple, Union, Any

_HEADER_FOOTER_FORMAT: str = '<2sHQ{data}2s'

_MSG_ID: int = 0


HEADER_MAGIC: bytes = b'RT'
FOOTER_MAGIC: bytes = b'TR'


class Packer:
    FORMATS: Dict[int, str] = {}

    @classmethod
    def pack(cls, msg_type: int, *args: Any) -> bytes:
        global _MSG_ID
        header = (HEADER_MAGIC, msg_type, _MSG_ID)
        footer = (FOOTER_MAGIC,)
        args = header + args + footer
        _MSG_ID += 1
        return struct.pack(cls.FORMATS[msg_type], *args)
    
    @classmethod
    def unpack(cls, msg_type: int, data: bytes) -> Tuple[Any, ...]:
        return struct.unpack(cls.FORMATS[msg_type], data)
    
    @classmethod
    def calcsize(cls, msg_type: int) -> int:
        return struct.calcsize(cls.FORMATS[msg_type])


class Server(Packer):
    FORMATS: Dict[int, str] = {
        0x0000: _HEADER_FOOTER_FORMAT.format(data='Q'),
        0x0001: _HEADER_FOOTER_FORMAT.format(data='H'),
        0x0002: _HEADER_FOOTER_FORMAT.format(data='H'),
        0x0003: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0004: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0010: _HEADER_FOOTER_FORMAT.format(data='Hff'),
        0x0011: _HEADER_FOOTER_FORMAT.format(data='H?'),
        0x0012: _HEADER_FOOTER_FORMAT.format(data='Hff'),
        0x0013: _HEADER_FOOTER_FORMAT.format(data='Hh'),
        0x0020: _HEADER_FOOTER_FORMAT.format(data='Hff'),
        0x0021: _HEADER_FOOTER_FORMAT.format(data='H'),
        0x0022: _HEADER_FOOTER_FORMAT.format(data='Hff'),
        0x0030: _HEADER_FOOTER_FORMAT.format(data='Hffff'),
        0x0031: _HEADER_FOOTER_FORMAT.format(data='Hff'),
        0x0032: _HEADER_FOOTER_FORMAT.format(data='HH'),
        0x0033: _HEADER_FOOTER_FORMAT.format(data='H'),
    }
    ConnectAck: int = 0x0000
    RoomInformation: int = 0x0001
    LevelInformation: int = 0x0002
    GameStarted: int = 0x0003
    GameEnded: int = 0x0004
    PlayerSpawn: int = 0x0010
    PlayerDeath: int = 0x0011
    PlayerMovement: int = 0x0012
    PlayerWeaponSwitch: int = 0x0013
    EnemySpawn: int = 0x0020
    EnemyDeath: int = 0x0021
    EnemyMovement: int = 0x0022
    BulletShoot: int = 0x0030
    BulletPosition: int = 0x0031
    BulletHit: int = 0x0032
    BulletDespawn: int = 0x0033

class Client(Packer):
    FORMATS: Dict[int, str] = {
        0x0000: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0001: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0002: _HEADER_FOOTER_FORMAT.format(data='H'),
        0x0003: _HEADER_FOOTER_FORMAT.format(data='H'),
        0x0004: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0005: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0010: _HEADER_FOOTER_FORMAT.format(data='ff????'),
        0x0011: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0012: _HEADER_FOOTER_FORMAT.format(data=''),
        0x0013: _HEADER_FOOTER_FORMAT.format(data='h'),
        0xFF00: _HEADER_FOOTER_FORMAT.format(data='Q'),
    }
    Connect: int = 0x0000
    Disconnect: int = 0x0001
    ChooseRoom: int = 0x0002
    ChooseLevel: int = 0x0003
    StartGame: int = 0x0004
    CreateRoom: int = 0x0005
    PlayerMovement: int = 0x0010
    PlayerShoot: int = 0x0011
    PlayerReload: int = 0x0012
    PlayerSwitchWeapon: int = 0x0013
    Ack: int = 0xFF00

