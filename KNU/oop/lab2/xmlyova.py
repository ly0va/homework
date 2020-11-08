#!/usr/bin/python3
import gi
import lxml.etree as etree
import webbrowser

gi.require_version('Gtk', '3.0')

from gi.repository import Gtk as gtk
from strategy import *

class UI(gtk.Window):

    def __init__(self, filename):
        super().__init__(title="XMLyova")
        with open(filename) as xml:
            self.xml = xml.read()
        self.parser_type = 'DOM'
        self.init_widgets()

    def init_widgets(self):
        self.set_default_size(900, 600)
        self.connect('destroy', gtk.main_quit)
        panes = gtk.Box()
        panes.pack_start(self.left_pane(), True, True, 0)
        panes.pack_start(self.right_pane(), True, True, 0)
        main = gtk.VBox()
        main.pack_start(self.create_toolbar(), False, False, 0)
        main.pack_start(panes, True, True, 0)
        self.add(main)

    def left_pane(self):
        controls = gtk.VBox(spacing=10)
        controls.set_margin_top(10)
        controls.set_margin_start(50)
        controls.set_margin_end(50)
        controls.set_margin_bottom(50)
        controls.add(self.create_label('Search Parameters'))
        controls.add(self.create_dropdowns())
        controls.add(self.create_label('Parser Type'))
        controls.add(self.create_radio())
        controls.add(self.create_label('Action'))
        controls.add(self.create_buttons())
        return controls

    def create_label(self, text):
        label = gtk.Label()
        label.set_markup(f'<b><big>{text}</big></b>')
        return label

    def create_dropdowns(self):
        vbox = gtk.VBox(spacing=3)
        cds = DOMParser().parse(self.xml)
        self.dropdowns = {}
        for field in FIELDS:
            box = gtk.Box()
            label = gtk.Label(label=field.capitalize())
            dropdown = gtk.ComboBoxText()
            dropdown.set_size_request(250, 0)
            dropdown.append_text('')
            for option in sorted(set(cd[field] for cd in cds)):
                dropdown.append_text(option)
            self.dropdowns[field] = dropdown
            box.pack_start(label, False, False, 0)
            box.pack_end(dropdown, False, False, 0)
            vbox.add(box)
        return vbox

    def create_radio(self):
        box = gtk.Box(spacing=50)
        dom_button = gtk.RadioButton(label='DOM')
        sax_button = gtk.RadioButton(label='SAX')
        sax_button.join_group(dom_button)
        dom_button.connect('toggled', self.set_parser)
        sax_button.connect('toggled', self.set_parser)
        box.add(dom_button)
        box.add(sax_button)
        return box

    def create_buttons(self):
        buttons = gtk.Box(spacing=10)
        search = gtk.Button(label='Search')
        search.connect('clicked', self.search)
        transform = gtk.Button(label='Transform')
        transform.connect('clicked', self.transform)
        buttons.pack_start(search, True, True, 0)
        buttons.pack_start(transform, True, True, 0)
        return buttons

    def set_parser(self, widget, data=None):
        self.parser_type = widget.get_label()

    def format_cd(self, cd, number):
        text = f'\n--- CD #{number} ---\n'
        for field in FIELDS:
            text += f'{field.capitalize()}: {cd[field]}\n'
        return text

    def search(self, widget, data=None):
        parser = DOMParser() if self.parser_type == 'DOM' else SAXParser()
        cds = parser.parse(self.xml)
        text = '*** Search Results ***\n'
        for i, cd in enumerate(cds, 1):
            include_cd = True
            for field in FIELDS:
                parameter = self.dropdowns[field].get_active_text()
                if parameter and parameter != cd[field]:
                    include_cd = False
            if include_cd:
                text += self.format_cd(cd, i)
        self.set_text(text)

    def transform(self, widget, data=None):
        xml = etree.parse('./cdcatalog.xml')
        xsl = etree.parse('./cdcatalog.xsl')
        html = etree.XSLT(xsl)(xml)
        html_string = etree.tostring(html, pretty_print=True).decode()
        self.set_text(html_string)
        with open('./cdcatalog.html', 'w') as html_file:
            html_file.write(html_string)
        webbrowser.open_new_tab("./cdcatalog.html")

    def right_pane(self):
        window = gtk.ScrolledWindow()
        window.set_min_content_width(400)
        self.text_view = gtk.TextView(
            editable=False,
            monospace=True,
            cursor_visible=False
        )
        window.add(self.text_view)
        return window

    def set_text(self, text):
        buffer = gtk.TextBuffer(text=text)
        self.text_view.set_buffer(buffer)

    def create_toolbar(self):
        toolbar = gtk.Toolbar()
        quit = gtk.ToolButton(stock_id=gtk.STOCK_QUIT)
        info = gtk.ToolButton(stock_id=gtk.STOCK_ABOUT)
        toolbar.insert(quit, 0)
        toolbar.insert(info, 1)
        quit.connect("clicked", lambda _: self.confirm_exit())
        info.connect("clicked", lambda _: self.info(
            "XMLyova v0.1.0", 
            "Lab 2, Lev Potyomkin, K-27"
        ))
        return toolbar

    def info(self, primary, secondary=''):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.INFO,
            buttons=gtk.ButtonsType.OK,
            text=primary,
        )
        dialog.format_secondary_text(secondary)
        dialog.run()
        dialog.destroy()

    def confirm_exit(self):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.QUESTION,
            buttons=gtk.ButtonsType.OK_CANCEL,
            text='Are you sure you want to quit?'
        )
        response = dialog.run()
        dialog.destroy()
        if response == gtk.ResponseType.OK:
            gtk.main_quit()

    def error(self, message):
        dialog = gtk.MessageDialog(
            transient_for=self,
            message_type=gtk.MessageType.ERROR,
            buttons=gtk.ButtonsType.CANCEL,
            text=message,
        )
        dialog.run()
        dialog.destroy()


if __name__ == '__main__':
    ui = UI('./cdcatalog.xml')
    ui.show_all()
    gtk.main()

