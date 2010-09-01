/**
 * @file estadoMenuCanciones.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#include "juego.h"
#include "estadoCancion.h"

#include "estadoMenuCanciones.h"

EstadoMenuCanciones::EstadoMenuCanciones(Juego * p)
	: Estado(p), cancion(0){

	estadoTransicion = transIn;

	// CONFIGURACIÓN DE LA IMAGEN DEL LOGOTIPO
	imgLogotipo.reset(new ElementoImagen(padre -> graphics(),
	                                     "media/ofluteLogoGrande.png",
	                                     3, Animacion::tAlpha));

	imgLogotipo -> setXY(75, 100);
	imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
	imgLogotipo -> animacion -> set(0, 0, 255);


	imgSeleccion.reset(new ElementoImagen(padre -> graphics(),
	                                      "media/selCanMark.png",
	                                      3, Animacion::tPos));

	imgSeleccion -> animacion = new Animacion(2, 30, Animacion::tEaseOutCubic, 10);
	imgSeleccion -> animacion -> set(0, 800, 397);
	imgSeleccion -> animacion -> set(1, 200, 200);

	// CONFIGURACIÓN DEL SUBTÍTULO
	txtSubtitulo.reset(new ElementoTexto(padre -> graphics(),
	                                     _("Seleccione una canción"),
	                                     "media/fNormal.ttf",
	                                     34, Gosu::Color(0xffa4a4a4),
	                                     Texto::alignCentro,
	                                     true, 10, 3, 
	                                     Animacion::tAlpha));

	txtSubtitulo -> setXY(180, 425);
	txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
	txtSubtitulo -> animacion -> set(0, 0, 255);




	boost::shared_ptr<EntradaMenuCanciones> E(
		new EntradaMenuCanciones(padre -> graphics(),
		                         "Título de prueba",
		                         "Descripción de prueba blablabla",
		                         "", 0)
		);

	conjuntoCanciones.push_back(E);

}

void EstadoMenuCanciones::update(){
	if(estadoTransicion == transIn){
		if(imgLogotipo -> animacion -> finished() &&
		   txtSubtitulo -> animacion -> finished()){
			estadoTransicion = transHold;
		}
	}

	if(cancion != 0) {
		cancion -> update();
	}
}

void EstadoMenuCanciones::draw(){
	if(estadoTransicion == mostrandoCancion){
		cancion -> draw();
	}else{
		imgLogotipo -> draw();
		txtSubtitulo -> draw();
		conjuntoCanciones[0] -> draw();
		imgSeleccion -> draw();
	}
}

void EstadoMenuCanciones::buttonDown(Gosu::Button boton){
	if(cancion != 0)
		cancion -> buttonDown(boton);

	if(boton == Gosu::kbEscape){
		padre -> cambiarEstado("estadoMenuSinFondo");
	}

	else if(boton == Gosu::kbReturn){

		lDEBUG << "Se pulsó enter";

		cancion.reset(new Cancion(padre -> graphics(), "song1.xml"));
		cancion -> lanzar();

		estadoTransicion = mostrandoCancion;
	}

   
}

EstadoMenuCanciones::~EstadoMenuCanciones(){

}

