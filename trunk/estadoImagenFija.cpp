#include "estadoImagenFija.h"
#include "juego.h"

EstadoImagenFija::EstadoImagenFija (Juego * p, 
				    wstring nombreImagen, 
				    string estadoSiguiente, 
				    unsigned tiempoEspera) 
    : Estado(p), 
      nombreImagen(nombreImagen), 
      estadoSiguiente(estadoSiguiente),
      tiempoEspera(tiempoEspera){
    cout << "** EstadoImagenFija::CONSTRUCTOR" << endl;
}

void EstadoImagenFija::lanzar(){
    cout << "* EstadoImagenFija lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
    alphaActual = 0;

    // Poblamos el puntero de la imagen de fondo
    imgFondo.reset(new Gosu::Image(padre -> graphics(), nombreImagen));
}

void EstadoImagenFija::update(){
    if(!lanzado) return;
    short step = 6;

    // 0: Haciendo el fade in
    if(estadoAnim == 0){
	alphaActual += step;

	if(alphaActual > 255){
	    alphaActual = 255;
	    estadoAnim = 1;
	    tiempoEsperaInicial = Gosu::milliseconds();
	}
    }

    // 1: Manteniendo
    else if(estadoAnim == 1){
	if(Gosu::milliseconds() - tiempoEsperaInicial > tiempoEspera){
	    estadoAnim = 2;
	}
    }

    // 2: Haciendo el fadeout
    else if(estadoAnim == 2){
	alphaActual -= step;
	if(alphaActual < 0){
	    alphaActual = 0;
	    // padre -> cambiarEstado("estadoIntro");
	    accionPosterior();
	}
    }
}

void EstadoImagenFija::draw(){
    if(!lanzado) 
	return;
    
    imgFondo -> draw(0,0,1,1,1,Gosu::Color(alphaActual,255,255,255));
}

void EstadoImagenFija::buttonDown(Gosu::Button boton){
    if(!lanzado) return;
    if (boton == Gosu::kbEscape){
//	padre -> cambiarEstado("estadoIntro");
//	padre -> close();
	accionPosterior();
    }else{
	cout << "KABOOM" << endl;
    }
}

void EstadoImagenFija::accionPosterior(){
    padre -> cambiarEstado(estadoSiguiente);
}

EstadoImagenFija::~EstadoImagenFija(){
    cout << "** EstadoImagenFija::DESTRUCTOR" << endl;
}
