# Generated by Django 2.2.1 on 2019-07-04 18:12

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('initial', '0003_auto_20190704_1746'),
    ]

    operations = [
        migrations.AlterField(
            model_name='coordenada',
            name='time',
            field=models.DateTimeField(verbose_name='instante'),
        ),
    ]