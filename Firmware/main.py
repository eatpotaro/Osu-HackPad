import board
import busio
import displayio
import terminalio

from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.scanners import DiodeOrientation
from kmk.modules.display import Display, TextEntry

keyboard = KMKKeyboard()

keyboard.col_pins = (board.GP8, board.GP9, board.GP10, board.GP11)
keyboard.row_pins = ()
keyboard.diode_orientation = DiodeOrientation.COLUMNS

keyboard.keymap = [[KC.D, KC.F, KC.J,KC.K,]]

displayio.release_displays()

i2c = busio.I2C(board.GP6, board.GP7)  # SDA, SCL

display = Display(
    i2c=i2c,
    driver="SSD1306",
    width=128,
    height=32,
    rotation=0,
)

last_key_text = TextEntry(
    text="Last key: -",
    x=0,
    y=10,
    font=terminalio.FONT,
)

display.entries = [last_key_text]
keyboard.modules.append(display)

def record_key(key, pressed, **kwargs):
    if pressed:
        if key == KC.D:
            last_key_text.text = "Last key: D"
        elif key == KC.F:
            last_key_text.text = "Last key: F"
        elif key == KC.J:
            last_key_text.text = "Last key: J"
        elif key == KC.K:
            last_key_text.text = "Last key: K"

keyboard.before_matrix_scan = record_key

if __name__ == "__main__":
    keyboard.go()
