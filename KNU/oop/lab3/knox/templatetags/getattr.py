from django.template import Library

register = Library()

# Create your views here.
@register.filter(name='getattr')
def getattrfilter(o, attr):
    try:
        return getattr(o, attr)
    except:
        return ''
