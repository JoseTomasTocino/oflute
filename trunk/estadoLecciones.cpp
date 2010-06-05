#include "juego.h"
#include "estadoLecciones.h"
#include "leccion.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "pugixml.hpp"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {

    estadoActual = eMostrando;

    leccionMostrada = NULL;
    leccionActual = -1;

    pizarra.reset(new ElementoImagen(padre -> graphics(), "media/menuLecciones/pizarra.png", 2, Animacion::tAlphaPos));
    pizarra -> animacion = new Animacion(3, 30, Animacion::tEaseOutQuad, 0);
    pizarra -> animacion -> set(0, 0, 255); // alfa
    pizarra -> animacion -> set(1, -450, 35); // x
    pizarra -> animacion -> set(2, 128, 128); // y

    
    /* 

    t = new tConfAnim;
    t -> animar = Animacion::tPos;
    t -> inicialY = -70;
    t -> z = 2;
    barraSuperior.reset(new ElementoCombinado( padre -> graphics(), *t));
    delete t;

    tConfTexto * cTexto = new tConfTexto();

    cTexto-> cadena = "Listado de lecciones";
    cTexto-> rutaFuente = "media/fLight.ttf";
    cTexto-> tam = 56;
    
    barraSuperior -> setTexto(*cTexto, 34, 0);
			
    delete cTexto;

    barraSuperior -> setImagen("media/menuLecciones/mTop.png");



    // Barra inferior

    tConfAnim * confInferior = new tConfAnim();
    confInferior -> animar = Animacion::tPos;
    confInferior -> inicialY = 600;
    confInferior -> finalY = 554;
    confInferior -> z = 2;
    barraInferior.reset(new ElementoCombinado(padre -> graphics(), *confInferior));

    barraInferior -> setImagen("media/menuLecciones/mBottom.png");

    tConfTexto * confInferiorTexto = new tConfTexto;
    confInferiorTexto -> cadena = "Volver al menú";
    confInferiorTexto -> rutaFuente = "media/fNormal.ttf";
    confInferiorTexto -> tam = 28;
    barraInferior -> setTexto(*confInferiorTexto, 52, 7);

    delete confInferior;
    delete confInferiorTexto;



    // Primer botón

    tConfAnim * confBtn = new tConfAnim();
    confBtn -> animar = Animacion::tPos;
    confBtn -> inicialX = 800;
    confBtn -> finalX = 400;
    confBtn -> inicialY = confBtn -> finalY = 69;
    confBtn -> wait = 10;
    confBtn -> duracion = 20;
    confBtn -> z = 2;
    btnTitular.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btnTitular -> setImagen("media/menuLecciones/mBtn1.png");

    tConfTexto * confBtnTexto = new tConfTexto;
    confBtnTexto -> cadena = "Lección nº1";
    confBtnTexto -> rutaFuente = "media/fNormal.ttf";
    confBtnTexto -> tam = 36;
    confBtnTexto -> sombra = false;
    confBtnTexto -> alineacion = Texto::alignDer;
    btnTitular -> setTexto(*confBtnTexto, -20, 7);




    ///////////////////////////////
    // Descripción
    confBtn -> inicialY = confBtn -> finalY = 127;
    confBtn -> wait = 20;
    btnDescripcion.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btnDescripcion -> setImagen("media/menuLecciones/mBtn2.png");

    confBtnTexto -> cadena = "Descripción:";
    confBtnTexto -> sombra = true;
    confBtnTexto -> color = Gosu::Color(255, 227, 253, 94);
    btnDescripcion -> setTexto(*confBtnTexto, -20, 10);

    tConfTexto tdConf;
    tdConf.cadena = " ";
    tdConf.rutaFuente = "media/fNormal.ttf";
    tdConf.tam = 36;
    tdConf.alineacion = Texto::alignDer;

    tConfAnim tdConfA;
    tdConfA.finalX = 780;
    tdConfA.finalY = 175;
    tdConfA.finalA = 255;
    tdConfA.z = 4;

    textoDesc . reset (new ElementoTexto(padre -> graphics(), tdConf, tdConfA));

    ///////////////////////////////
    // Botón comenzar 
    confBtn -> inicialY = confBtn -> finalY = 351;
    confBtn -> wait = 30;
    btnComenzar.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btnComenzar -> setImagen("media/menuLecciones/mBtn3.png");
    confBtnTexto -> color = Gosu::Color(255,255,255,255);
    confBtnTexto -> cadena = "Comenzar lección";
    confBtnTexto -> alineacion = Texto::alignCentro;
    btnComenzar -> setTexto(*confBtnTexto, 10, 10);


    ///////////////////////////////
    // Botón Siguiente Lección
    confBtn -> inicialY = confBtn -> finalY = 417;
    confBtn -> wait = 40;
    btnSigLec.reset(new ElementoCombinado(padre -> graphics(), *confBtn));
    btnSigLec -> setImagen("media/menuLecciones/mBtn4.png");

    confBtnTexto -> cadena = "Siguiente lección";
    btnSigLec -> setTexto(*confBtnTexto, 10, 13);


    /////////////////////////////
    // Botón Anterior Lección
    confBtn -> inicialY = confBtn -> finalY = 487;
    confBtn -> wait = 50;
    btnAntLec.reset(new ElementoCombinado(padre -> graphics(), *confBtn));
    btnAntLec -> setImagen("media/menuLecciones/mBtn5.png");

    confBtnTexto -> cadena = "Anterior lección";
    btnAntLec -> setTexto(*confBtnTexto, 10, 10);


    delete confBtn;
    delete confBtnTexto;

    //*/


}

void EstadoMenuLecciones::listarLecciones(){


    boost::filesystem::path rutaDirectorio("./lecciones");
    boost::filesystem::directory_iterator inicial(rutaDirectorio), final;

    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;
    pugi::xml_attribute atributo;

    for(; inicial != final ; ++ inicial){
	if(boost::to_lower_copy(inicial -> path() . extension()) == ".xml"){

	    EstadoMenuLecciones::infoLeccion lecActual;
	    string ruta = boost::lexical_cast<string>(inicial -> path());

	    lDEBUG << "Intentando cargar archivo " << ruta;

	    resultado = documento . load_file(ruta.c_str());

	    if(!resultado){
		lERROR << LOC() << " Error al leer el documento: " << ruta;
		lERROR << resultado.description(); 
		continue;
	    }

	    lecActual.ruta = ruta;

	    /////////////////////
	    // Leemos el número de lección

	    nodoActual = documento.child("Lec").child("index");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta índice)";
		continue;
	    }

	    lecActual.indice = boost::lexical_cast<int>(nodoActual.first_child().value());


	    /////////////////
	    // Leemos el nombre de la lección

	    nodoActual = documento.child("Lec").child("nombre");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta nombre)";
		continue;
	    }

	    lecActual.nombre = nodoActual.first_child().value();


	    /////////////////////
	    // Leemos la descripción
	    nodoActual = documento.child("Lec").child("descrip");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta descripción)";
		continue;
	    }

	    lecActual.descrip = nodoActual.first_child().value();

	    leccionesCargadas.push_back(lecActual);

	}
    }

    sort(leccionesCargadas.begin(), leccionesCargadas.end(), ordenarLecciones());
    leccionActual = 0;
    cambiarLeccion(leccionActual);
}



void EstadoMenuLecciones::cambiarLeccion(unsigned n){
    leccionActual = n;

    tConfTexto * confBtnTexto = new tConfTexto;
    confBtnTexto -> cadena = string("Lección nº") + boost::lexical_cast<string>(leccionesCargadas[n].indice);
    confBtnTexto -> rutaFuente = "media/fNormal.ttf";
    confBtnTexto -> tam = 36;
    confBtnTexto -> sombra = false;
    confBtnTexto -> alineacion = Texto::alignDer;
    btnTitular -> setTexto(*confBtnTexto, -20, 7);

    delete confBtnTexto;

    textoDesc -> setText(leccionesCargadas[n] . descrip);
}



void EstadoMenuLecciones::iniciarAnimacionSalida(){
    pizarra -> animacion -> setTipoAnimacion(Animacion::tEaseInQuad);
    pizarra -> animacion -> set(0, 255, 0); // alfa
    pizarra -> animacion -> set(1, 35, -450); // x
    pizarra -> animacion -> set(2, 128, 128); // y
    pizarra -> animacion -> init();
}



void EstadoMenuLecciones::draw() {
    pizarra -> draw();

    /*
    barraInferior -> draw();  

    if(estadoActual == eMenu || estadoActual == eMostrando || estadoActual == eOcultando){
	pizarra -> draw();
	barraSuperior -> draw();
	btnTitular -> draw();
	textoDesc -> draw();
	btnComenzar -> draw();
	btnAntLec -> draw();
	btnSigLec -> draw();
	btnDescripcion -> draw();
    }else if(estadoActual == eLeccion){
	leccionMostrada -> draw();
    }
	
    //*/
}

void EstadoMenuLecciones::anteriorLec(){
    if(leccionActual <= 0){
	cambiarLeccion(leccionesCargadas.size() - 1);
    }else{
	cambiarLeccion(leccionActual - 1);
    }
	
}

void EstadoMenuLecciones::siguienteLec(){
    if(leccionActual == (int)(leccionesCargadas.size() - 1)){
	cambiarLeccion(0);
    }else{
	cambiarLeccion(leccionActual + 1);
    }
}


void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	if(estadoActual == eMenu){
	    estadoActual = eOcultando;
	    iniciarAnimacionSalida();
	}
	else{
	    padre -> cambiarEstado("estadoMenuSinFondo");
	}
    }
#ifdef ON
    else if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();
	
	if(estadoActual == eMenu){
	    if(barraInferior -> clicked(x, y)){
		padre -> cambiarEstado("estadoMenuSinFondo");
	    }
	    
	    else if(btnAntLec -> clicked(x, y)){
		anteriorLec();
	    }

	    else if(btnSigLec -> clicked(x, y)){
		siguienteLec();
	    }
	    
	    else if(btnComenzar -> clicked(x, y)){
		lanzarLeccion();
	    }
	}

	else if(estadoActual == eLeccion){	    
	    if(barraInferior -> clicked(x, y)){
		estadoActual = eMenu;
		delete leccionMostrada;
		leccionMostrada = NULL;
	    }
	}

    }
#endif

}

void EstadoMenuLecciones::lanzarLeccion(){
    lDEBUG << LOC();
    estadoActual = eOcultando1;
    
/*    leccionMostrada = new Leccion(padre -> graphics(), 
				  leccionesCargadas[leccionActual].ruta);
    estadoActual = eLeccion;//*/
    
}

void EstadoMenuLecciones::update(){
    if(pizarra -> animacion -> finished() &&
       1 ){

	if(estadoActual == eMostrando){
	    estadoActual = eMenu;
	}
	else if(estadoActual == eOcultando){
	    padre -> cambiarEstado("estadoMenuSinFondo");
	}
    }

#ifdef ON
    if((btnTitular -> animacion -> finished()) && leccionActual == -1){
	listarLecciones();
    }

    if(btnAntLec -> animacion -> finished() && estadoActual < eMenu){
	estadoActual = eMenu;
    }
#endif
}


EstadoMenuLecciones::~EstadoMenuLecciones(){
    if(leccionMostrada != NULL){
	delete leccionMostrada;
    }
}
