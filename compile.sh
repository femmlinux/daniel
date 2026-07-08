#!/bin/bash

set -e

echo "🔨 Compilando Daniel Taskbar..."

# Verificar dependencias
echo "📦 Verificando dependencias..."

if ! pkg-config --exists gtk+-3.0; then
    echo "❌ gtk+-3.0 no encontrado. Instalando..."
    sudo pacman -S gtk3
fi

if ! pkg-config --exists gtk-layer-shell-0; then
    echo "❌ gtk-layer-shell no encontrado. Instalando..."
    sudo pacman -S gtk-layer-shell
fi

# Compilar
echo "⚙️  Compilando daniel.c..."
gcc -o daniel daniel.c \
    $(pkg-config --cflags --libs gtk+-3.0 gtk-layer-shell-0)

echo "✅ Compilación exitosa!"
echo "🚀 Ejecuta: ./daniel"
