'''
MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

'''

from bs4 import BeautifulSoup
from pathlib import Path
import base64

original_html_text = Path('index.html').read_text(encoding="utf-8")
soup = BeautifulSoup(original_html_text)

# Find link tags. example: <link rel="stylesheet" href="css/somestyle.css">
for tag in soup.find_all('link', href=True):
    if tag.has_attr('href'):
        file_text = Path(tag['href']).read_text(encoding="utf-8")

        # remove the tag from soup
        tag.extract()

        # insert style element
        new_style = soup.new_tag('style')
        new_style.string = file_text
        soup.html.head.append(new_style)


# Find script tags. example: <script src="js/somescript.js"></script>
for tag in soup.find_all('script', src=True):
    if tag.has_attr('src'):
        file_text = Path(tag['src']).read_text()

        # remove the tag from soup
        tag.extract()

        # insert script element
        new_script = soup.new_tag('script')
        new_script.string = file_text
        soup.html.body.append(new_script)

# Create the 'dist' directory if it doesn't exist
Path("dist").mkdir(parents=True, exist_ok=True)

# Save onefile
with open("dist/oneindex.html", "w", encoding="utf-8") as outfile:
    outfile.write(str(soup))