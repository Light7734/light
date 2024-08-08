# Project information
project = 'Light'
copyright = '2024, Light7734'
author = 'Light7734'
release = '1'

# General configuration
extensions = [
    "sphinx.ext.intersphinx",
    "sphinx_copybutton",
    "sphinx_design"
]

source_suffix = '.rst'
default_role = 'cpp:any'
pygments_style = 'sphinx'
highlight_language = 'c++'
primary_domain = 'cpp'
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

templates_path = ["_templates"]

# Theme configuration
html_theme = 'sphinx_rtd_theme'
# html_favicon = ''
