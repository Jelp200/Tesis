# Diagramas de bloques :framed_picture:
A continuación se presentan los diagramas a blloques de la solución.

## Diagrama general del sistema electrónico.
A continuación en la siguiente figura se puede visualizar el diagrama a bloques general del sistema electrónico.

<div>
    <img src="/HARDWARE/Diagramas de bloques/Diagrama general del sistema electronico.png" />
</div>

###### <b><i>Nota.</i></b> El color anaranjado presentre en la figura anterior representa la parte del sistema electrónico analógico, mientras que el color azul representa la parte del sistema electrónico digital.
<ul>
    <li><b><i>Sistema de adquisición de la señal.</b></i></li> Este sistema nos permite adquirir la señal de fotopletismografía (PPG) a través de dos diodos emisores de luz (LED's) de diferentes longitudes de onda. Estas longitudes de onda penetrarán el la piel que a su vez los vasos sanguíneos absorberán y relfejarán la luz emitida por cada LED, esto para que un fotorepector funja como transductor y pueda detecrar el cambio de volumen sanguíneo, y así la señal PPG. 
    <li><b><i>Sistema de adecuamiento de la señal.</b></i></li> Este sistema nos permite adecuar la señal PPG una vez adquirida por el sistema de adquisición. En este punto se filtra la señal PPG para trabajar con las frecuencias deseadas, y se amplifica.
    <li><b><i>Sistema de procesamiento de la señal.</b></i></li> Este sistema nos permite digitalizar la señal PPG ya adecuada, a una señal digital para su procesamiento y posterior visualización a traves de la aplicación móvil y web.
</ul>