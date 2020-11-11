#!/usr/bin/python3
import gi
import lxml.etree as etree
import webbrowser

gi.require_version('Gtk', '3.0')

from gi.repository import Gtk as gtk
from strategy import *

## UI constants
WINDOW_WIDTH = 900
WINDOW_HEIGHT = 600
CONTROLS_SPACING = 10
CONTROLS_MARGIN = 50
BUTTONS_SPACING = 10
RADIO_SPACING = 50
DROPDOWNS_SPACING = 3
DROPDOWNS_WIDTH = 250
TEXTAREA_WIDTH = 400
FILENAME = 'cdcatalog'

class UI(gtk.Window):

    def __init__(self, filename):
        super().__init__(title="XMLyova")
        with open(filename) as xml:
            self.xml = xml.read()
        self.parser_type = 'DOM'
        self.dropdowns = {}
        self.init_widgets()
        self.dom_parser = DOMParser(self.xml)
        self.sax_parser = SAXParser(self.xml)

    def init_widgets(self):
        self.set_default_size(WINDOW_WIDTH, WINDOW_HEIGHT)
        self.connect('destroy', gtk.main_quit)
        panes = gtk.Box()
        panes.pack_start(self.left_pane(), True, True, 0)
        panes.pack_start(self.right_pane(), True, True, 0)
        main = gtk.VBox()
        main.pack_start(self.create_toolbar(), False, False, 0)
        main.pack_start(panes, True, True, 0)
        self.add(main)

    def left_pane(self):
        controls = gtk.VBox(spacing=CONTROLS_SPACING)
        controls.set_margin_start(CONTROLS_MARGIN)
        controls.set_margin_end(CONTROLS_MARGIN)
        controls.set_margin_bottom(CONTROLS_MARGIN)
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
        vbox = gtk.VBox(spacing=DROPDOWNS_SPACING)
        try:
            cds = DOMParser(self.xml).parse({})
        except Exception:
            self.error('Invalid format of the XML document')
            gtk.main_quit()
        for field in FIELDS:
            box = gtk.Box()
            label = gtk.Label(label=field.capitalize())
            dropdown = gtk.ComboBoxText()
            dropdown.set_size_request(DROPDOWNS_WIDTH, 0)
            dropdown.append_text('')
            for option in sorted(set(cd[field] for cd in cds)):
                dropdown.append_text(option)
            self.dropdowns[field] = dropdown
            box.pack_start(label, False, False, 0)
            box.pack_end(dropdown, False, False, 0)
            vbox.add(box)
        return vbox

    def create_radio(self):
        box = gtk.Box(spacing=RADIO_SPACING)
        dom_button = gtk.RadioButton(label='DOM')
        sax_button = gtk.RadioButton(label='SAX')
        sax_button.join_group(dom_button)
        dom_button.connect('toggled', self.set_parser)
        sax_button.connect('toggled', self.set_parser)
        box.add(dom_button)
        box.add(sax_button)
        return box

    def create_buttons(self):
        buttons = gtk.Box(spacing=BUTTONS_SPACING)
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
        parser = self.dom_parser \
            if self.parser_type == 'DOM' \
            else self.sax_parser
        params = {field: dropdown.get_active_text()
                  for field, dropdown in self.dropdowns.items()}
        cds = parser.parse(params)
        text = '*** Search Results ***\n' + \
            ''.join(self.format_cd(cd, i) for i, cd in enumerate(cds, 1))
        self.set_text(text)

    def transform(self, widget, data=None):
        xml = etree.fromstring(self.xml.encode())
        xsl = etree.parse(f'./{FILENAME}.xsl')
        html = etree.XSLT(xsl)(xml)
        html_string = etree.tostring(html, pretty_print=True).decode()
        self.set_text(html_string)
        with open(f'./{FILENAME}.html', 'w') as html_file:
            html_file.write(html_string)
        webbrowser.open_new_tab(f"./{FILENAME}.html")

    def right_pane(self):
        window = gtk.ScrolledWindow()
        window.set_min_content_width(TEXTAREA_WIDTH)
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
    ui = UI(f'./{FILENAME}.xml')
    ui.show_all()
    gtk.main()

