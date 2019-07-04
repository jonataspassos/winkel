from django.shortcuts import render
from django.http import HttpResponse
from initial.utils import add_coordenada

# Create your views here.

def index(request):
    return HttpResponse("Hello, world.")

def saveCoord(request,pitch,roll,yaw):
    print("Pitch: "+str(pitch)+" Roll: "+str(roll)+" Yaw: "+str(yaw))
    return HttpResponse(add_coordenada(pitch,roll,yaw))
