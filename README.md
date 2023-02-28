# cryptChange

cryptChange is a simple POC programm to theoretically swap BTC addresses in the clipboard. This was made because, after WannaCry, I wanted to see for myself what it takes so make a super simple malware.

For **educational purposes** ONLY!

## Prerequisites

- C++ compiler

## Installation

Use `git clone` to download the repository to your local machine:

```bash
> git clone https://github.com/Pyenb/cryptChange
```

## Usage

Execute the `build.bat` to build the executable

When executed, the resulting `manager.exe` will constanly look for regex patterns matching to a BTC address and swap it out with whatever value was defined.

Use the `clean.bat` to clean the PC from the executable

## AV Evasion

This tool has no kind of antivirus evasion implemented, as it is not designed for any real world applications. Windows Defender will flag this almost instantly.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Disclaimer
This repository is for research purposes only, the use of this code is your responsibility.

I take NO responsibility and/or liability for how you choose to use any of the source code available here. By using any of the files available in this repository, you understand that you are AGREEING TO USE AT YOUR OWN RISK. Once again, ALL files available here are for EDUCATION and/or RESEARCH purposes ONLY.
