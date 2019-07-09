from initial.models import Coordenada
from django.utils import timezone

def add_coordenada(pitch,roll,yaw):
    d = Coordenada(time=timezone.now(),pitch=pitch,roll=roll,yaw=yaw)
    d.save()
    return "Ok"

def getValueBack():
    valorBanco = Coordenada.objects.latest('time')
    respBanco = {}
    respBanco['time'] = valorBanco.time
    respBanco['pitch'] = valorBanco.pitch
    respBanco['roll'] = valorBanco.roll
    respBanco['yaw'] = valorBanco.yaw
    return respBanco
