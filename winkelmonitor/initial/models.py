from django.db import models
from django.utils import timezone

# Create your models here.

class Coordenada(models.Model):
    time = models.DateTimeField('instante')
    pitch = models.FloatField()
    yaw = models.FloatField()
    roll = models.FloatField()
    def __str__(self):
        return str(self.time)+" Pitch:"+str(self.pitch)+" Yaw:"+str(self.yaw)+" Roll:"+str(self.roll)

