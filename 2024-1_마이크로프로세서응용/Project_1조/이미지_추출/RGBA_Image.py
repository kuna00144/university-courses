from intelhex import IntelHex
from PIL import Image
import numpy as np

def hex_to_rgba_png(input_hex_file, output_png_file, start_address, end_address, image_width):
    ih = IntelHex(input_hex_file)
    data = []

    for address in range(start_address, end_address):
        byte = ih[address]
        r = (byte >> 5) & 0x07  # Extract R (3 bits)
        g = (byte >> 2) & 0x07  # Extract G (3 bits)
        b = byte & 0x03         # Extract B (2 bits)

        # Scale up to 8 bits
        r = (r << 5) | (r << 2) | (r >> 1)
        g = (g << 5) | (g << 2) | (g >> 1)
        b = (b << 6) | (b << 4) | (b << 2) | b

        a = 255  # Max alpha value
        data.extend([r, g, b, a])

    data_array = np.array(data, dtype=np.uint8)
    image_height = len(data_array) // (image_width * 4)
    image_data = data_array[:image_width * image_height * 4].reshape((image_height, image_width, 4))
    image = Image.fromarray(image_data, 'RGBA')
    image.save(output_png_file)

input_hex_file = 'Optimization_Image_Output.hex'
output_png_file = 'Optimization_Image_Output.png'
start_address = 0x30000000
end_address = 0x30096000
image_width = 960

hex_to_rgba_png(input_hex_file, output_png_file, start_address, end_address, image_width)
