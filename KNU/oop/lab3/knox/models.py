from django.db import models


class Currency(models.Model):
    class Meta:
        verbose_name_plural = "Currencies"

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

    def __str__(self):
        return self.name

    name = models.CharField(max_length=64)
    description = models.TextField()


class Reminder(models.Model):
    def __str__(self):
        return f'Reminder about {self.category}'

    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    comment = models.TextField()
    time = models.DateTimeField(auto_now_add=True)

class Income(models.Model):
    account = models.ForeignKey(Account, on_delete=models.CASCADE)
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    amount = models.BigIntegerField()
    date = models.DateField(auto_now_add=True)

class Transfer(models.Model):
    from_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_from_account')
    to_account = models.ForeignKey(Account, on_delete=models.CASCADE, related_name='transfer_to_account')
    from_amount = models.BigIntegerField()
    to_amount = models.BigIntegerField()
    date = models.DateField(auto_now_add=True)

