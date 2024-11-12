import subprocess
import streamlit as st
from PIL import Image
import os

# Directories for input and output images
input_dir = "data/input/"
output_dir = "data/output/"
executable = "bin/cimg_lab"  # Path to the C++ executable

# Set up the application title and description
st.title("Cimg lab Application")

# Option to upload an image or use a default image
uploaded_file = st.file_uploader("Choose an image...", type=["jpg", "png"])
use_default_image = st.checkbox("Use default image (eagle.jpg)")

# Define paths for input and output images
input_path = os.path.join(input_dir, "input_image.jpg")
output_path = os.path.join(output_dir, "output_image.jpg")

# Load or save the selected image to the input directory
if uploaded_file is not None:
    # Save the uploaded image to the input directory
    with open(input_path, "wb") as f:
        f.write(uploaded_file.getbuffer())
elif use_default_image:
    # Use the default image if no image is uploaded
    input_path = os.path.join(input_dir, "eagle.jpg")
    original_image = Image.open(input_path)

# Select box for choosing the image processing operation
operation = st.selectbox("Choose an operation", ["Gradient", "Blur", "math_transformations",
                                                 "fill", "contrast", "erosion", "dilation",
                                                 "opening", "closing", "kramer"])

# Display the original image in the first column
if uploaded_file is not None:
    original_image = Image.open(uploaded_file)
    col1, col2 = st.columns(2)  # Set up two columns for side-by-side display
    col1.image(original_image, caption="Original Image", use_container_width=True)
else:
    try:
        col1, col2 = st.columns(2)  # Set up two columns for side-by-side display
        col1.image(original_image, caption="Default Image", use_container_width=True)
    except:
        st.warning("Please upload an image or select the default image option.")

# Map the selected operation to a command-line argument
operation_arg = operation.lower()  # Matches the operation name used in main.cpp

# Button to execute the selected operation
if st.button("Calculate"):
    if uploaded_file is not None or use_default_image:
        # Run the C++ executable with the selected operation
        result = subprocess.run([executable, operation_arg, input_path, output_path],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        if result.returncode == 0:
            # Load and display the processed image in the second column
            result_image = Image.open(output_path)
            col2.image(result_image, caption=f"{operation} Image", use_container_width=True)
            st.success(f"{operation} calculation complete.")
        else:
            # Display an error message if processing fails
            st.error("There was an error processing the image.")
            st.text("Error details:")
            st.text(result.stderr.decode("utf-8"))
    else:
        # Display a warning if no image is uploaded or selected
        st.warning("Please upload an image or select the default image option.")
