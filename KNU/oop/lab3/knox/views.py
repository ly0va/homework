from django.shortcuts import render, redirect, get_object_or_404
from .models import Currency
from .forms import CurrencyForm
from django.views.generic import ListView, DetailView

def index(model):
    class Index(ListView):
        template_name = 'knox/index.html'
        context_object_name = 'entity_list'
        def get_queryset(self):
            return model.objects.all()
    return Index

def detail(model_):
    class Detail(DetailView):
        model = model_
        template_name = 'knox/details.html'
        def get_context_data(self, **kwargs):
            context = super().get_context_data(**kwargs)
            context['fields'] = self.model._meta.fields
            return context
    return Detail

def create(model_form, scope):
    def create(request):
        if request.method == 'POST':
            form = model_form(request.POST)
            if form.is_valid():
                form.save()
                return redirect(f'index_{scope}')
        form = model_form()
        return render(request, 'knox/create.html', {'form': form})
    return create

def edit(model, model_form, scope):
    def edit(request, pk, template_name='knox/edit.html'):
        entity = get_object_or_404(model, pk=pk)
        form = model_form(request.POST or None)
        if form.is_valid():
            form.save()
            return redirect(f'index_{scope}')
        return render(request, template_name, {'form': form})
    return edit

def delete(model, scope):
    def delete(request, pk, template_name='knox/confirm_delete.html'):
        entity = get_object_or_404(model, pk=pk)
        if request.method == 'POST':
            entity.delete()
            return redirect(f'index_{scope}')
        return render(request, template_name, {'object': entity})
    return delete
