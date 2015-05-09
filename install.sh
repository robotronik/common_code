PACMAN="sudo pacman -S --needed"
YAOURT="yaourt      -S --needed"

########## Mise à jour 
#sudo pacman-mirrors -g
sudo pacman -Suuyy

if [[ ! `which yaourt` ]]; then
	echo "Erreur, il faut installer Yaourt pour installer les paquets utiles !"
fi
yaourt -Suya

########## Desktop
#$PACMAN gnome-terminal meld gnome-calculator baobab
#$YAOURT sublime-text-dev

########## Méca
$PACMAN openscad 
$YAOURT repetier-host

########## Électronique
##TODO à vérifier
$YAOURT kicad-bzr kicad-pretty-git kicad-docs-bzr kicad-library-bzr 

########## Compilation + git
$PACMAN gcc gdb git 
$PACMAN sdl sdl_image soil


########## uContrôleurs
$PACMAN picocom #arduino

# STM32
$YAOURT stm32cubef4 arm-none-eabi-binutils arm-none-eabi-gcc arm-none-eabi-gdb arm-none-eabi-newlib


# PIC
$YAOURT xc16-toolchain-bin pk2cmd-plus 
