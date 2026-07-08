# Daniel - Ultra-lightweight Wayland Taskbar

Una barra de tareas ultraligera para Wayland con estilo visual clásico de **Windows XP**.

## Características

✨ **Diseño Windows XP Clásico**
- Gradiente azul en la barra superior
- Botón de inicio verde brillante con texto en itálica
- Reloj digital en la bandeja del sistema (derecha)
- Interfaz limpia y minimalista

⚡ **Rendimiento Optimizado**
- Desarrollado en C puro
- Utiliza GTK+ 3.0 y gtk-layer-shell para máxima eficiencia
- Consumo mínimo de RAM
- Compatible con Wayland

🎮 **Funcionalidades**
- **Botón Start**: Abre el menú de aplicaciones (`wofi`)
- **Atajo de teclado**: Presiona `Super` (tecla Windows) para abrir aplicaciones
- **Reloj automático**: Se actualiza cada segundo

## Requisitos

### Arch Linux

```bash
sudo pacman -S gtk3 gtk-layer-shell wofi
```

### Otras distros

- GTK+ 3.0
- gtk-layer-shell
- wofi (o tu lanzador de aplicaciones preferido)

## Instalación y Compilación

### Opción 1: Usando Makefile (Recomendado)

```bash
# Compilar
make

# Ejecutar
make run

# Instalar en ~/.local/bin
make install

# Limpiar binarios
make clean
```

### Opción 2: Usando script de compilación

```bash
chmod +x compile.sh
./compile.sh
./daniel
```

### Opción 3: Compilación manual

```bash
gcc -o daniel daniel.c $(pkg-config --cflags --libs gtk+-3.0 gtk-layer-shell-0)
./daniel
```

## Uso

```bash
./daniel
```

La barra de tareas aparecerá en la parte inferior de la pantalla con:
- Botón **Start** a la izquierda
- **Reloj digital** a la derecha
- Espacio flexible en el medio para futuras extensiones

## Customización

Para cambiar estilos, edita las variables CSS en `daniel.c`:
- Colores del gradiente: `#0078d4`, `#1084d7`, `#0a66bb`
- Color del botón Start: `#00aa00`
- Color de la bandeja: `#1f5ba0`

## Características Futuras

- [ ] Icono de volumen
- [ ] Indicador de batería
- [ ] Panel de control mini
- [ ] Soporte para temas personalizados
- [ ] Icono de conexión de red

## Licencia

MIT

## Autor

Creado como un proyecto minimalista de barra de tareas para Wayland.
