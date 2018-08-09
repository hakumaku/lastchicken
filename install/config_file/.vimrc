" =====================
" Vundle
" https://github.com/VundleVim/Vundle.vim.git
" =====================
" {{{
" git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
" call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
	Plugin 'VundleVim/Vundle.vim'

	" Colorschemes
	" Plugin 'altercation/vim-colors-solarized'
	Plugin 'lifepillar/vim-solarized8'
	Plugin 'morhetz/gruvbox'
	Plugin 'octol/vim-cpp-enhanced-highlight'
	Plugin 'junegunn/seoul256.vim'
	Plugin 'crusoexia/vim-monokai'

	Plugin 'scrooloose/syntastic'
	Plugin 'tpope/vim-surround'
	Plugin 'raimondi/delimitmate'
	Plugin 'scrooloose/nerdtree'

	Plugin 'tpope/vim-fugitive'

	Plugin 'vim-airline/vim-airline'
	Plugin 'vim-airline/vim-airline-themes'

	Plugin 'mattn/emmet-vim'

	Plugin 'Valloric/YouCompleteMe'
	Plugin 'pangloss/vim-javascript'
	Plugin 'artur-shaik/vim-javacomplete2'

	" arm syntax highlighting
	Plugin 'arm9/arm-syntax-vim'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just
" :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to
" auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this lineset nocompatible
" }}}
" =====================


" =====================
" Vim Basic Settings
" =====================
" {{{
syntax on
set t_Co=256			" True colors
if (has("termguicolors"))
	 set termguicolors
endif

set hidden				" Hide buffers when abandoned
set number				" Show line number
set tabstop=4			" Tab size = 4
set shiftwidth=4		" Size of the indent
set softtabstop=0		" Insert a combination of spaces when set to non-zero
set noexpandtab			" No spaces when tab
set autoindent
set listchars=tab:»\ ,eol:↲,trail:·

set scrolloff=3			" Show 3 lines above or below cursor when scrolling
set showmode			" Show insert, replace, or visual mode in last line
set showcmd				" Show command in last line
set encoding=utf-8		" Encoding
set nobackup			" No backup files
set nowritebackup		" No backup files

set splitbelow			" When opening h splits, place cursor in the new split
set splitright			" When opening v splits, place cursor in the new split

set cursorline			" Show cursor line
set incsearch			" Dynamic search
set hlsearch			" Highlight search
set laststatus=2
" Replace - with ' '
set fillchars=fold:\ 
set signcolumn="yes"
" }}}
" =====================


" =====================
" Vim Functions
" =====================
" {{{
func EatChar(pat)
	let c = nr2char(getchar(0))
	return (c =~ a:pat) ? '' : c
endfunc

func Replace()
	call inputsave()
	let word = input('Replace with: ')
	call inputrestore()
	execute '%s/'.@".'/'.word.'/gc'
endfunc

func ExactReplace()
	call inputsave()
	let word = input('Replace with: ')
	call inputrestore()
	execute '%s/\<'.@".'\>/'.word.'/gc'
endfunc

" The following three functions are for better 'iab'.
func! EatWhitespace()
	let c = nr2char(getchar())
	return (c =~ '\s') ? '' : c
endfunc

func! MapNoContext(key, seq)
	let syn = synIDattr(synID(line('.'), col('.')-1, 1), 'name')
	if syn =~? 'comment\|string\|character\|doxygen'
		return a:key
	else
		exe 'return "'.
		    \substitute(a:seq, '\\<\(.\{-}\)\\>', '"."\\<\1>"."', 'g').
			\'"'
	endif
endfunc

func! Iab (ab, full)
	exe "iab <silent> <buffer> ".a:ab." <C-R>=MapNoContext('".
		\a:ab."', '".escape(a:full.'<C-R>=EatWhitespace()<CR>', '<>"').
		\"')<CR>"
endfunc
" }}}
" =====================


" =====================
" Customized Shortcut
" =====================
" {{{
" Insert a newline in normal mode.
nnoremap <C-L> o<Esc>
" Move the current line one down.
nnoremap <C-j> :m+1<CR>:echo 'Move line down'<CR>
" Move the current line one up.
nnoremap <C-k> :m-2<CR>:echo 'Move line up'<CR>
" Open.
nnoremap <C-o> :NERDTreeToggle<CR>:echo @%<CR>
" Toggle displaying whitespaces.
nnoremap <F3> :set nolist!<CR>
" Insert space in normal mode
nnoremap <space> i<space><esc>
" Toggle .vimrc file.
nnoremap <expr> <Home> bufname('%') == $MYVIMRC ? ':bd<CR>' : ':e $MYVIMRC<CR>'
" Replace
vnoremap <C-h> y:call Replace()<CR>
" Exact replace
vnoremap <C-g> y:call ExactReplace()<CR>

" Cycle through buffers
nnoremap <tab> :bn<CR>
nnoremap <delete> :bd<CR>

" Execute python file
au FileType python noremap <buffer> <F9> :exec '!python3' shellescape(@%, 1)<CR>

" Execute bash file
au FileType sh noremap <buffer> <F9> :exec '!bash' shellescape(@%, 1)<CR>
" }}}
" =====================


" =====================
" Autocommand
" =====================
" {{{
augroup project
	au!
	au BufRead,BufNewFile *.h,*.c set filetype=c
	au BufRead,BufNewFile * setlocal signcolumn=yes
augroup END

augroup file_c
	au!
	" Insert comment
	au FileType c call Iab('icom', '/*  */<esc>2<Left>i')
	au FileType c call Iab('com', '/*<CR> <CR>/<Up>')
	" Insert #include
	au FileType c call Iab('Inc', '#include <.h><esc>2ba')
	" Insert C main function
	au FileType c call Iab('Main', 'int main(int argc, const char *argv[])<CR>
					\{<CR>}<CR><esc><Up>Oreturn 0;<esc>O<esc>O')
	" if statement
	au FileType c call Iab('if', 'if ()<CR>{<CR>}<esc>2ba')
	au FileType c call Iab('elif', 'else if ()<CR>{<CR>}<esc>2ba')
	au FileType c call Iab('else', 'else<CR>{<CR>}<esc>O')
	au FileType c call Iab('while', 'while ()<CR>{<CR>}<esc>2ba')
	au FileType c call Iab('for', 'for (;;)<CR>{<CR>}<esc>2ba')
	au FileType c call Iab('switch', 'switch ()<CR>{<CR>default:<CR>break;<CR>}<esc>6ba')
augroup END

augroup file_cc
	au!
	" Insert comment
	au FileType cpp call Iab('icom', '/*  */<esc>2<Left>i')
	au FileType cpp call Iab('com', '/*<CR> <CR>/<Up>')
	" Insert #include
	au FileType cpp call Iab('Inc', '#include <.h><esc>2ba')
	" Insert C main function
	au FileType cpp call Iab('Main', 'int main(int argc, const char *argv[])<CR>
					\{<CR>}<CR><esc><Up>Oreturn 0;<esc>O<esc>O')
	" if statement
	au FileType cpp call Iab('if', 'if ()<CR>{<CR>}<esc>2ba')
	au FileType cpp call Iab('elif', 'else if ()<CR>{<CR>}<esc>2ba')
	au FileType cpp call Iab('else', 'else<CR>{<CR>}<esc>O')
	au FileType cpp call Iab('while', 'while ()<CR>{<CR>}<esc>2ba')
	au FileType cpp call Iab('for', 'for (;;)<CR>{<CR>}<esc>2ba')
	au FileType cpp call Iab('switch', 'switch ()<CR>{<CR>default:<CR>break;<CR>}<esc>6ba')
augroup END

augroup file_py
	au!
	au FileType python call Iab('from', 'from  import <esc>b<Left>i')
	au FileType python call Iab('if', 'if :<Left>')
	au FileType python call Iab('elif', 'elif :<Left>')
	au FileType python call Iab('else', 'else:<CR>')
	au FileType python call Iab('while', 'while :<Left>')
	au FileType python call Iab('for', 'for  in :<esc>B<Left>i')
	au FileType python call Iab('def', 'def ():<CR>pass<esc>2Bi')
	au FileType python call Iab('class', 'class ():<CR>def __init__(self, *args, **kwargs):<CR>pass<esc>4Bi')
	au FileType python call Iab('try', 'try:<CR>pass<CR><CR>except :<CR>pass<esc>2bi')
	au FileType python call Iab('pdb', 'import pdb; pdb.set_trace()')
	" au FileType python call Iab('Main', 'if __name__ == ''__main__'':<CR>main()<CR>')
augroup END

augroup file_java
	au!
	au FileType java setlocal omnifunc=javacomplete#Complete
augroup END

augroup color_theme
	au!
	" Set the color of them to that of LineNr
	au ColorScheme * hi! def link SignColumn LineNr
	au ColorScheme * hi! def link Error LineNr
	au Colorscheme * hi! def link Folded Normal
	" Whitespaces
	" au ColorScheme * hi! def link SpecialKey Normal
augroup END

augroup file_vim
	au!
	au FileType vim setlocal foldmethod=marker
augroup END
" }}}
" =====================


" =====================
" tmux
" =====================
" {{{
" Tmux true color settings.
let &t_8f = "\<Esc>[38;2;%lu;%lu;%lum"
let &t_8b = "\<Esc>[48;2;%lu;%lu;%lum"
" }}}
" =====================


" =====================
" vim-solarized8
" https://github.com/lifepillar/vim-solarized8
" =====================
" {{{
" set background=dark
" silent! colorscheme solarized8
" silent! colorscheme solarized8_low
" silent! colorscheme solarized8_high
" silent! colorscheme solarized8_flat
" }}}
" =====================


" =====================
" gruvbox
" https://github.com/morhetz/gruvbox
" =====================
" {{{
set background=dark
silent! colorscheme gruvbox
let g:gruvbox_invert_indent_guides=1
let g:gruvbox_contrast='hard'
" }}}
" =====================


" =====================
" vim-monokai
" https://github.com/crusoexia/vim-monokai
" =====================
" {{{
" silent! colorscheme monokai
" }}}
" =====================


" =====================
" seoul256
" https://github.com/junegunn/seoul256.vim
" =====================
" {{{
" set background=dark
" Range:   233 (darkest) ~ 239 (lightest)
" Default: 237
" let g:seoul256_background = 233
" silent! colorscheme seoul256
" }}}
" =====================


" =====================
" vim-syntastic
" =====================
" {{{
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_c_checkers = ['gcc']
let g:syntastic_c_compiler = 'gcc'
let g:syntastic_c_compiler_options = '-std=c99'
let g:syntastic_cpp_compiler_options = '-std=c++14'
let g:syntastic_loc_list_height=1
let g:ycm_show_diagnostics_ui = 0
let g:syntastic_python_python_exec = 'python3'
" }}}
" =====================


" =====================
" vim-airline & vim-airline-themes
" =====================
" {{{
let g:airline#extensions#tabline#enabled = 1			" turn on buffer list
let g:airline#extensions#tabline#show_tab_nr = 1		" Show tab number
let g:airline#extensions#tabline#tab_nr_type = 1		" Show tab number
let g:airline#extensions#tabline#fnamemod = ':t'		" Display only file name
let g:airline_section_b = '%{strftime("%H:%M:%S")}'
let g:airline#extensions#whitespace#mixed_indent_algo = 1
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#buffer_idx_mode = 1	" Show buffer number
" let g:airline_theme='light'
" let g:airline_solarized_bg='dark'
" }}}
" =====================


" =====================
" vim-emmet
" =====================
" {{{
" let g:user_emmet_leader_key='<Tab>'
" }}}
" =====================


" =====================
" YouCompleteMe
" =====================
" {{{
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'
" Disable scratch window.
set completeopt-=preview
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_autoclose_preview_window_after_insertion = 1
let g:ycm_python_binary_path = '/usr/bin/python3'
noremap <F5> :YcmForceCompileAndDiagnostics<CR>
" }}}
" =====================


" =====================
" arm-syntax-vim
" =====================
" {{{
au BufNewFile,BufRead *.s,*.S set filetype=arm " arm = armv6/7
" }}}
" =====================

