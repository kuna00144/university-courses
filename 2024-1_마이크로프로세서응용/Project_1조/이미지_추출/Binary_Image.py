from intelhex import IntelHex
from PIL import Image
import numpy as np

def hex_to_grayscale_png(input_hex_file, output_png_file, start_address, end_address, image_width):
    ih = IntelHex(input_hex_file)
    data = []

    for address in range(start_address, end_address):
        byte = ih[address]
        for bit in range(8):
            value = (byte >> (7 - bit)) & 0x01
            grayscale_value = 0xFF if value == 1 else 0x00
            r = g = b = grayscale_value
            a = 255
            data.extend([r, g, b, a])

    data_array = np.array(data, dtype=np.uint8)
    image_height = len(data_array) // (image_width * 4)
    image_data = data_array[:image_width * image_height * 4].reshape((image_height, image_width, 4))
    image = Image.fromarray(image_data, 'RGBA')
    image.save(output_png_file)

input_hex_file = 'Optimization_Binary_Image_Output.hex'
output_png_file = 'Optimization_Binary_Image_Output.png'
start_address = 0x30000000
end_address = 0x30012000
image_width = 960

hex_to_grayscale_png(input_hex_file, output_png_file, start_address, end_address, image_width)