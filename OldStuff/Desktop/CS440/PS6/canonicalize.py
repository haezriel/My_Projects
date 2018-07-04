import os
import string
import operator

_VALID_CHARS = string.ascii_lowercase+string.ascii_uppercase+string.digits
_TRANS_TABLE = ''.join([(e if e in _VALID_CHARS else ' ') for e in 
                  string.maketrans(string.ascii_lowercase + 
                                   string.ascii_uppercase,
                                   string.ascii_lowercase * 2)])

def canonicalize(fname):
    """
    Read a file from disk, translating it into canonical form.
    
    fname - a filename/path
    
    returns: a string representation of the file in it's "canonical
      form". Here, whitespace has been sanitized (so words are separated
      by single spaces and no line breaks remain) and text has been
      transformed to lower-case and non-alphanumeric characters have
      been replaced with spaces."""

    tr = None
    with open(fname, 'r') as fin:
        text = fin.read()
        tr = ' '.join(text.translate(_TRANS_TABLE).split())
    return tr
