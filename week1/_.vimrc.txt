set visualbell
set belloff=all
set vb
filetype plugin on
" show existing tab with 4 spaces width
set tabstop=4
" when indenting with '>', use 4 spaces width
set shiftwidth=4
" On pressing tab, insert 4 spaces
set expandtab

set clipboard=unnamed
" Removes all white space when saving
autocmd BufWritePre * :%s/\s\+$//e

" copy indent from current line when starting a new line
set autoindent

" make backspaces more powerfull
set backspace=indent,eol,start
set clipboard=unnamedplus

" For rust
" Also download the rust vim extensions
syntax enable
