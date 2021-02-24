from distutils.core import setup

setup(
    name="loderunnerclient",
    version="1.0",
    description="Lode Runner Dojo game client",
    author="",
    author_email="",
    packages=["loderunnerclient", "loderunnerclient.internals"],
    install_requires=["websocket-client", "click"],
    entry_points={"console_scripts": ["loderunnerclient=loderunnerclient.Main:main"]},
)
