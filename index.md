# Pi Pico and Godot (PROYECTO AÚN EN DESARROLLO)
## Comunicación entre una Pi Pico y Godot mediante la Serial

![pico_godot](/proyecto/imgs/pico_godot_der.png)


# Resumen
Este proyecto se trata solamente de demostrar el funcionamiento de Godot con la Serial para que se le sea posible comunicarse con dispositivos que se comuniquen mediante esta. En este caso se prenderá un LED mediante un programa hecho en Godot.

# Introducción
Godot es un Engine para crear videojuegos, pero quiero saber si se le es posible comunicarse mediante la Serial para así interactuar con dispositivos I/O. La Raspberry Pi Pico (RPP), es un minicontrolador el cual ya he utilizado en un anterior proyecto, por lo que ya se cuenta con conocimiento previo del uso básico del minicontrolador. El realizar este proyecto es con el objetivo de asegurar que Godot puede realizar esta comunicación para iniciar demás proyectos que incluyan este proyecto como base; y es que tengo pensado realizar un teclado modular pero necesito una GUI para modificar sus teclas sin necesidad de hacer un nuevo sketch en Arduino. Ah, y trabajeroms con Arduino IDE para programar a la Pi Pico.

# Desarollo
Ahora sí, lo primero que se realizó fue un diagrama del circuito para pasarlo en físico.
![fotodeldiagrama](/proyecto/imgs/pipico_circuito.drawio.png)