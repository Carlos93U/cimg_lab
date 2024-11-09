import subprocess
import streamlit as st
from PIL import Image
import os

# Directories for input and output images
input_dir = "data/input/"
output_dir = "data/output/"
executable = "bin/cimg_lab"  # Path to the C++ executable

# Application title
st.title("Image Gradient Calculator")

# Option to upload an image or use the default image
uploaded_file = st.file_uploader("Choose an image...", type="jpg")
use_default_image = st.checkbox("Use default image (eagle.jpg)")

# Define paths for input and output images
input_path = os.path.join(input_dir, "input_image.jpg")
output_path = os.path.join(output_dir, "output_image.jpg")

# Save the selected image or use the default image
if uploaded_file is not None:
    # Save the uploaded image to the input directory
    with open(input_path, "wb") as f:
        f.write(uploaded_file.getbuffer())
elif use_default_image:
    # Use the default image
    input_path = os.path.join(input_dir, "eagle.jpg")

# Button to calculate the gradient
if st.button("Calculate Gradient"):
    if uploaded_file is not None or use_default_image:
        # Run the C++ executable to process the image
        result = subprocess.run([executable, input_path, output_path])

        if result.returncode == 0:
            # Display the resulting gradient image in streamlit
            result_image = Image.open(output_path)
            st.image(result_image, caption="Gradient Image")
            st.success("Gradient calculation complete.")
        else:
            st.error("There was an error processing the image.")
    else:
        st.warning("Please upload an image or select the default image option.")
