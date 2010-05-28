@echo off
latex -src lshort.tex
makeindex -o lshort.ind lshort.idx
latex -src lshort.tex
latex -src lshort.tex
dvipdfmx lshort.dvi
del *.aux
del *.toc
del *.lof
del *.lot
del *.ilg
del *.idx
del *.ind
del *.out
del *.log
del *.exa
@echo on
pause
