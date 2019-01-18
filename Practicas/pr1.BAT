(deftemplate usuario
	(slot dameprecio (type INTEGER) )
	(slot damemaletero (allowed-values pequenio mediano grande) (default grande))
	(slot damecaballos ( type INTEGER ) )
	(slot dameabs (allowed-values si no) (default si))
	(slot dameconsumo ( type FLOAT ) )
)
	



(deftemplate coches
	(slot modelo (type STRING))
	(slot precio (type INTEGER) ))
	(slot maletero (allowed-values pequenio mediano grande) (default grande))
	(slot caballos ( type INTEGER ) )
	(slot abs (allowed-values si no) (default si))
	(slot consumo ( type FLOAT ) )
)
	
(deffacts modelo
	(coches  (modelo modelo1)
		 (precio 12000)
		 (maletero pequenio)
		 (caballos 65)
		 (abs no)
		 (consumo 4,7))
	(coches  (modelo modelo2)
		 (precio 12500)
		 (maletero pequenio)
		 (caballos 80)
		 (abs si)
		 (consumo 4,9))
	(coches  (modelo modelo3)
		 (precio 13000)
		 (maletero mediano)
		 (caballos 100)
		 (abs si)
		 (consumo 7,8))
	(coches  (modelo modelo4)
 		 (precio 14000)
		 (maletero grande)
		 (caballos 125)
		 (abs si)
		 (consumo 6,0))
	(coches  (modelo modelo5)
		 (precio 15000)
		 (maletero pequenio)
		 (caballos 147)
		 (abs si)
		 (consumo 8,5))
)
(reset)

(defrule precios
		
	(coches (modelo ?x) (precio ?p) )
	(usuario (dameprecio ?p) ())
=>(printout t "El modelo seleccionado es" ?x crlf)
)

(defrule maletero
	
	(coches (modelo ?x) (maletero ?m) )
	(usuario (damemaletero ?m) ())
=>(printout t "El modelo seleccionado es" ?x crlf)
)	

(defrule caballos
		
	(coches (modelo ?x) (caballos ?c) )
	(usuario (damecaballos ?c) ())
=>(printout t "El modelo seleccionado es" ?x crlf)
)

(defrule abs
		
	(coches (modelo ?x) (abs ?a) )
	(usuario (dameabs ?a) ())
=>(printout t "El modelo seleccionado es" ?x crlf)
)

(defrule consumo
		
	(coches (modelo ?x) (comsumo ?co) )
	(usuario (dameconsumo ?co) ())
=>(printout t "El modelo seleccionado es" ?x crlf)
)



assert(usuario(dameprecio(13000)))


