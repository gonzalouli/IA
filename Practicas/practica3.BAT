(deftemplate valvula
	(slot nombre)
	(slot estado (allowed-values abierta cerrada)(default cerrada)) 
	(slot presion (default 0)(type INTEGER))
	(slot tempint (default 0)(type INTEGER))
	(slot tempext (default 0)(type INTEGER))
)

(deffacts 
	(valvula(nombre Entrada) (tempint 101) (tempext 35) (presion 1) )
	(valvula(nombre Salida) (tempint 101) (tempext 155) (presion 5) )
	(valvula (nombre Pasillo1) (tempint 99) (tempext 37) (estado cerrada))
)

(deffunction aumento (?presion ?tempint)
	(while (> ?tempint 35)
	(bind ?presion(+ ?presion 1))
	(bind ?tempint(- ?tempint 5))
	)
	(return ?presion)
)

(deffuction decremento (?T1 ?T2)
	(if (< ?T1 ?T2) then
	(bind ?T2(- ?T2 ?T1)))
	(return ?T2)
)

(defrule R1 
	?a <-(valvula (nombre ?v) (estado abierta) (presion ?p)
	(TEST (= ?p 5)))
->
	(modify ?a (estado cerrada) (presion 0) ) )


(defrule R2
	?b <- (valvula (nombre ?v1) (estado cerrada) (presion ?p1)
	(test (< ?p1 10)) (tempint ?t1) (test (> ?t1 35)))
->
	(modify ?b (estado abrierta)(presion (aumento ?p1 ?t1) ) )
)

(defrule R3 
	?c <- (valvula (nombre ?v1) (tempint ?t1) (tempext ?t2 )
	?d <- (valvula (nombre ?v2&~?v1) (tempint ?t3) (tempext ?t2)) 			
	(test (< ?t1 ?t3))
	->
	(modify ?c (estado abierta) )
	(modify ?d (estado abierta)(tempext (decremento ?t3 ?t2) ) )
)




























