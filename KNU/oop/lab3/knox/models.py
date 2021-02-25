from django.db import models


class Currency(models.Model):
    class Meta:
        verbose_name_plural = "Currencies"

    class Type(models.IntegerChoices):
        FIAT = 0
        CRYPTO = 1

    name = models.CharField(max_length=64)
    symbol = models.CharField(max_length=8)
    decimals = models.SmallIntegerField()
    type = models.IntegerField(choices=Type.choices, default=Type.FIAT)


class Account(models.Model):
    class Type(models.IntegerChoices):
        CASH = 0
        DEBIT = 1
        CREDIT = 2
        SAVINGS = 3

    name = models.CharField(max_length=64)
    type = models.IntegerField(choices=Type.choices)
    currency = models.ForeignKey(Currency, on_delete=models.CASCADE)
    interest_rate = models.FloatField(default=0.0)
    amount = models.BigIntegerField()


class Category(models.Model):
    class Meta:
        verbose_name_plural = 'Categories'

    name = models.CharField(max_length=64)
    description = models.TextField()

class Reminder(models.Model):
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    comment = models.TextField()
    time = models.DateTimeField()

class Income(models.Model):
    account = models.ForeignKey(Account, on_delete=models.CASCADE)
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    amount = models.BigIntegerField()
    date = models.DateField()

class Transfer(models.Model):
    from_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_from_account')
    to_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_to_account')
    from_amount = models.BigIntegerField()
    to_amount = models.BigIntegerField()
    date = models.DateField()

