# Generated by Django 3.1.7 on 2021-03-25 14:05

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('knox', '0001_initial'),
    ]

    operations = [
        migrations.RenameField(
            model_name='account',
            old_name='type',
            new_name='kind',
        ),
        migrations.RenameField(
            model_name='currency',
            old_name='type',
            new_name='kind',
        ),
        migrations.AlterField(
            model_name='income',
            name='date',
            field=models.DateField(auto_now_add=True),
        ),
        migrations.AlterField(
            model_name='reminder',
            name='time',
            field=models.DateTimeField(auto_now_add=True),
        ),
        migrations.AlterField(
            model_name='transfer',
            name='date',
            field=models.DateField(auto_now_add=True),
        ),
    ]