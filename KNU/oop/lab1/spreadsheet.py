#!/usr/bin/python3
import gi

gi.require_version('Gtk', '3.0')
gi.require_version('Gdk', '3.0')

from gi.repository import Gtk as gtk, Gdk as gdk


class Table(gtk.Window):

    def __init__(self, cols, rows):
        super().__init__()
        self.cols = cols
        self.rows = rows
        self.set_default_size(600, 600)
        self.connect('destroy', gtk.main_quit)
        self.set_title("Lyova's Spreadsheet")
        self.set_border_width(8)
        vbox = gtk.VBox(homogeneous=False, spacing=8)
        self.add(vbox)
        label = gtk.Label(label='Nice to see you here')
        vbox.pack_start(label, False, False, 0)
        sw = gtk.ScrolledWindow()
        sw.set_shadow_type(gtk.ShadowType.ETCHED_IN)
        sw.set_policy(gtk.PolicyType.NEVER, gtk.PolicyType.AUTOMATIC)
        vbox.pack_start(sw, True, True, 0)

        types = [str] * self.cols
        self.liststore = gtk.ListStore(*types)
        for _ in range(self.rows):
            self.liststore.append(['0'] * self.cols)

        self.treeview = gtk.TreeView(model=self.liststore)
        sw.add(self.treeview)

        for i in range(self.cols):
            renderer = gtk.CellRendererText()
            renderer.set_property("editable", True)
            renderer.connect("edited", self.update)
            renderer.column = i
            column = gtk.TreeViewColumn(chr(ord('A')+i), renderer, text=i)
            self.treeview.append_column(column)

    def update(self, cell, row, text):
        self.liststore[row][cell.column] = text



manager = Table(26, 30)
manager.show_all()
gtk.main()


