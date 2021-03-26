"""lab3 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from knox import views
from knox.models import *
from knox.forms import *

def paths(model, model_form, scope):
    return [
        path(f'{scope}/', views.index(model).as_view(), name=f'index_{scope}'),
        path(f'{scope}/<int:pk>/', views.detail(model).as_view(), name=f'detail_{scope}'),
        path(f'{scope}/edit/<int:pk>/', views.edit(model, model_form, scope), name=f'edit_{scope}'),
        path(f'{scope}/create/', views.create(model_form, scope), name=f'create_{scope}'),
        path(f'{scope}/delete/<int:pk>/', views.delete(model, scope), name=f'delete_{scope}'),
    ]

urlpatterns = [
    # path('admin/', admin.site.urls),
    *paths(Currency, CurrencyForm, 'currencies'),
    *paths(Account, AccountForm, 'accounts'),
    *paths(Income, IncomeForm, 'incomes'),
    *paths(Transfer, TransferForm, 'transfers'),
    *paths(Reminder, ReminderForm, 'reminders'),
    *paths(Category, CategoryForm, 'categories'),
]
