
########## Desktop
PACMAN_PKG+=' gnome-terminal meld gnome-calculator  baobab zsh zsh-completions'

AUR_PKG+=' sublime-text-dev oh-my-zsh-git'

########## Méca
PACMAN_PKG+=' openscad'
AUR_PKG+=' repetier-host'

########## Électronique
PACMAN_PKG+=' kicad kicad-library'

########## Compilation + git
PACMAN_PKG+=' gcc gdb git'


########## uContrôleurs
PACMAN_PKG+=' picocom' #arduino

# STM32
AUR_PKG+=' stm32cubef4 arm-none-eabi-binutils arm-none-eabi-gcc arm-none-eabi-gdb arm-none-eabi-newlib'


# PIC
#$YAOURT xc16-toolchain-bin pk2cmd-plus

sudo pacman -S --needed $PACMAN_PKG

if [[ ! `which yaourt` ]]; then
    echo "Erreur, il faut installer Yaourt pour installer les paquets utiles !"
else
    yaourt -S --needed --noconfirm $AUR_PKG
fi


# Zshrc
cp /usr/share/oh-my-zsh/zshrc ~/.zshrc

