augroup project
	autocmd!
	autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

let &path.="src/include,/usr/include/AL,"
set makeprg=make\ -j4
nnoremap <F4> :make!<cr>
" ! prevents vim from jumping to first error found
nnoremap <F5> :!./build/main
" executing program!
syntax on
vsp
