from django.shortcuts import render
from django.http import HttpResponse
from initial.utils import add_coordenada, getValueBack
from django.http import JsonResponse

# Create your views here.

def index(request):
    #return HttpResponse("Hello, world.")
    context = {}
    return render(request, 'initial/index.html', context)

def saveCoord(request,pitch,roll,yaw):
    print("Pitch: "+str(pitch)+" Roll: "+str(roll)+" Yaw: "+str(yaw))
    return HttpResponse(add_coordenada(pitch,roll,yaw))

def getValue(request):
    return JsonResponse(getValueBack())

def teste(request,lalala):
    print(lalala)
    return HttpResponse('blz')