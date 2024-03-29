from django.urls import path,register_converter

from . import views, converters

register_converter(converters.FloatConverter,'float')

app_name = 'initial'

urlpatterns = [
    path('',views.index, name='index'),
    path('getvalue', views.getValue, name='getvalue'),
    path('<float:pitch>/<float:roll>/<float:yaw>',views.saveCoord, name='save_coord'),
    path('<str:lalala>',views.teste,name='teste'),
]
