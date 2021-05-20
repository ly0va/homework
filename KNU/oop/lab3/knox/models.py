# -*- coding: utf-8 -*-
from django.db import models
from django.urls import reverse


class Currency(models.Model):
    class Meta:
        verbose_name_plural = "Currencies"
        db_table = "currency"

    class Kind(models.IntegerChoices):
        FIAT = 0
        CRYPTO = 1

    def __str__(self):
        return self.name

    name = models.CharField(max_length=64)
    symbol = models.CharField(max_length=8)
    decimals = models.SmallIntegerField()
    kind = models.IntegerField(choices=Kind.choices, default=Kind.FIAT)


class Account(models.Model):
    class Meta:
        db_table = "account"

    class Kind(models.IntegerChoices):
        CASH = 0
        DEBIT = 1
        CREDIT = 2
        SAVINGS = 3

    def __str__(self):
        return self.name

    name = models.CharField(max_length=64)
    kind = models.IntegerField(choices=Kind.choices)
    currency = models.ForeignKey(Currency, on_delete=models.CASCADE)
    interest_rate = models.FloatField(default=0.0)
    amount = models.BigIntegerField()


class Category(models.Model):
    class Meta:
        verbose_name_plural = 'Categories'
        db_table = "category"

    def __str__(self):
        return self.name

    name = models.CharField(max_length=64)
    description = models.TextField()


class Income(models.Model):
    class Meta:
        db_table = "income"

    account = models.ForeignKey(Account, on_delete=models.CASCADE)
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    amount = models.BigIntegerField()
    date = models.DateField(auto_now_add=True)


class Transfer(models.Model):
    class Meta:
        db_table = "transfer"

    from_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_from_account')
    to_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_to_account')
    from_amount = models.BigIntegerField()
    to_amount = models.BigIntegerField()
    date = models.DateField(auto_now_add=True)
