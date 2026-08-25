import PyPDF2

# Open the PDF file
with open('example.pdf', 'rb') as file:
    reader = PyPDF2.PdfFileReader(file)
    text = ''
    for page in range(reader.numPages):
        text += reader.getPage(page).extract_text()

print(text)
