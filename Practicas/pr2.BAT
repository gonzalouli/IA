(deftemplate padre-de
	(multislot padre)
	(multislot hijo)
)
(deftemplate madre-de
	(multislot madre)
	(multislot hijo)
)
(deftemplate mujer-de
	(multislot esposa)
	(multislot esposo)
)
(deftemplate marido-de
	(multislot esposo)
	(multislot esposa)
)
(deftemplate abuelo-de
	(multislot abuelo)
	(multislot nieto)
)
(deftemplate abuela-de
	(multislot abuela)
	(multislt nieto)
)
(deftemplate hermano-de
	(multislot hermano1)
	(multislot hermano2)
)
(deftemplate hermana-de
	(multislot hermano1)
	(multislot hermano2)
)
(deftemplate primo-de
	(multislot primo1)
	(multislot primo2)
)
(deftemplate prima-de
	(multislot primo1)
	(multislot primo2)
)
(deftemplate tio-de 
	(multislot tio)
	(multislot sobrino)
)
(deftemplate tia-de 
	(multislot tia)
	(multislot sobrino)
)
(deftemplate nuera-de
	(multislot nuera)
	(multislot suegro)
)
(deftemplate yerno-de
	(multislot yerno)
	(multislot suegro)
)
(deftemplate cuñada-de
	(multislot cuñada)
	(multislot cuñado)
)
(deftemplate cuñado-de
	(multislot cuñado)
	(multislot cuñado)
)




(defrule hermanopp
	(padre-de (padre ?x) (hijo ?h1)) 
	(padre-de (padre ?x) (hijo ?h2&~?h1)) 
	(hombre ?h1)
	=>
	(assert (hermano-de (hermano1 ?h1) (hermano2 ?h2))
) )

(defrule hermanapp
	(padre-de (padre ?x) (hijo ?h1)) 
	(padre-de (padre ?x) (hijo ?h2&~?h1)) 
	(mujer ?h1)
	=>
	(assert (hermana-de (hermano1 ?h1) (hermano2 ?h2))
) 
)

(defrule hermanomm
	(madre-de (madre ?x) (hijo ?h1)) 
	(madre-de (madre ?x) (hijo ?h2&~?h1)) 
	(hombre ?h1)
	=>
	(assert (hermano-de (hermano1 ?h1) (hermano2 ?h2))
) )

(defrule hermanamm
	(madre-de (madre ?x) (hijo ?h1)) 
	(madre-de (madre ?x) (hijo ?h2&~?h1)) 
	(mujer ?h1)
	=>
	(assert (hermana-de (hermano1 ?h1) (hermano2 ?h2))
))

(defrule abuelo
	(padre-de (padre ?x) (hijo ?h1))
	(padre-de (padre ?a) (hijo ?x))
	(hombre ?a)
	=>
	(assert (abuelo-de (abuelo ?a) (nieto ?h1) )
))

(defrule abuela
	(padre-de (padre ?x) (hijo ?h1))
	(padre-de (padre ?a) (hijo ?x))
	(mujer ?a)
	=>
	(assert (abuela-de (abuelo ?a) (nieto ?h1) )
))

(defrule primopp
	(hermano-de (hermano ?x) (hermano2 ?y))
	(padre-de (padre ?x) (hijo ?p1))
	(padre-de (padre ?y&~?x) (hijo ?p2&~?p1))
	(hombre ?p1) 	
	=> 
	(assert (primo-de (primo1 ?p1) (primo2 ?p2))
))

(defrule primapp
	(hermano-de (hermano ?x) (hermano2 ?y))
	(padre-de (padre ?x) (hijo ?p1))
	(padre-de (padre ?y&~?x) (hijo ?p2&~?p1))
	(mujer ?p1) 	
	=> 
	(assert (prima-de (primo1 ?p1) (primo2 ?p2))
))
(defrule primomm
	(hermano-de (hermano ?x) (hermano2 ?y))
	(madre-de (madre ?x) (hijo ?p1))
	(madre-de (madre ?y&~?x) (hijo ?p2&~?p1))
	(hombre ?p1) 	
	=> 
	(assert (primo-de (primo1 ?p1) (primo2 ?p2))
))

(defrule primamm
	(hermano-de (hermano ?x) (hermano2 ?y))
	(madre-de (madre ?x) (hijo ?p1))
	(madre-de (madre ?y&~?x) (hijo ?p2&~?p1))
	(mujer ?p1) 	
	=> 
	(assert (prima-de (primo1 ?p1) (primo2 ?p2))
))

(defrule primopm
	(hermano-de (hermano ?x) (hermano2 ?y))
	(madre-de (madre ?x) (hijo ?p1))
	(padre-de (padre ?y&~?x) (hijo ?p2&~?p1))
	(mujer ?p1) 	
	=> 
	(assert (primo-de (primo1 ?p1) (primo2 ?p2))
))
(defrule primapm
	(hermano-de (hermano ?x) (hermano2 ?y))
	(padre-de (madre ?x) (hijo ?p1))
	(madre-de (madre ?y&~?x) (hijo ?p2&~?p1))
	(mujer ?p1) 	
	=> 
	(assert (prima-de (primo1 ?p1) (primo2 ?p2))
))


(defrule tiop
	(padre-de (padre ?x) (hijo ?h))
	(hermano-de (hermano1 ?h1) (hermano2 ?x)

	=>
	(assert (tio-de (tio ?h1) (sobrimo ?h) ) 
) )
(defrule tiom
	(madre-de (madre ?x) (hijo ?h))
	(hermano-de (hermano1 ?h1) (hermano2 ?x)

	=>
	(assert (tio-de (tio ?h1) (sobrimo ?h) ) 
) )

(defrule tiap
	(padre-de (padre ?x) (hijo ?h))
	(hermano-de (hermano1 ?h1) (hermano2 ?x)

	=>
	(assert (tia-de (tio ?h1) (sobrimo ?h) ) 
) )
(defrule tiam
	(madre-de (madre ?x) (hijo ?h))
	(hermano-de (hermano1 ?h1) (hermano2 ?x)

	=>
	(assert (tia-de (tio ?h1) (sobrimo ?h) ) 
) )



(defrule nuerap
	(mujer-de (esposa ?x) (esposo ?y)
	(padre-de (padre ?p) (hijo ?y)
	=>
	(assert (nuera-de (nuera ?x) (suegro ?p) ) 
) )
(defrule nueram
	(mujer-de (esposa ?x) (esposo ?y)
	(madre-de (madre ?p) (hijo ?y)
	=>
	(assert (nuera-de (nuera ?x) (suegro ?p) ) 
) )

(defrule yernop
	(marido-de (esposo ?x) (esposa ?y)
	(padre-de (padre ?p) (hijo ?y)
	=>
	(assert (yerno-de (yerno ?x) (suegro ?p) ) 
) )
(defrule yernom
	(marido-de (esposo ?x) (esposa ?y)
	(madre-de (madre ?p) (hijo ?y)
	=>
	(assert (yerno-de (yerno ?x) (suegro ?p) ) 
) )
	
(defrule cuñada
	(mujer-de (esposa ?x) (esposo ?y) )
	(hermano-de (hermano1 ?y) (hermano2 ?h) )
	=>
	(assert (cuñada-de (cuñada ?x) (cuñado ?h) ) 
) )

(defrule cuñado
	(hombre-de (esposo ?x) (esposa ?y) )
	(hermano-de (hermano1 ?y) (hermano2 ?h) )
	=>
	(assert (cuñado-de (cuñado ?x) (cuñado ?h) ) 
) )

















