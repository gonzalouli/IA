(defglobal anno=2025)
(deftemplate usuario
	(slot	dni)
	(slot	pin)
	(slot dinero (typeINTEGER)
)
(deftemplate tarjeta
	(slot pin)
	(slot dni)
	(slot intentos (default 3))
	(slot limite (default 6000))
	(slot expira (default 2018))
	(slot valida (allowed-values si no)(default no))
)
(deftemplate cuenta
	(slot dni)
	(slot estado (allowed-values enPantalla dineroEntregado Inicial SuperaLimite SinSaldo)(default Inicial))
)

(deffacts (tarjeta (dni 1234567) (pin 1212) (intentos 3) (limite 500) (expira 2018)(valida No))(cuenta (dni 1234567) (saldo 5000)
(estado inicial)
)


(deffunction menosuno (?i)
	(bind ?x (- ?i 1))
	(return ?x)
)

(deffunction diferencia (?a ?b)
	return(- ?a ?b)
) 


(defrule Supera_Intento
	(declare (salience 10))
    ?u<-(usuario(dni ?d)(pin ?p))
	(tarjeta(dni ?d)(pin ?p))
	(tarjeta (intentos 0))
	=> 
	(printout t "El numero de intentos ha sido sobrepasado" )
	(retract ?u)
)

	
(defrule Pin_Invalido
		(declare (salience 5))
	(usuario(dni ?d)(pin ?p))
	(tarjeta(dni ?d)(pin ~?p)(validada no)
	?t<-(tarjeta(intentos ?i))
	=>
	(printout t "El pin no es valido")
	(modify ?t(intentos (menosuno ?i)))
) 

(defrule Valida_Tarjeta
	(usuario(dni ?d)(pin ?p))
	?t<-(tarjeta(dni ?d)(pin ?p))
	(tarjeta (intentos  ?i)(valida no)(test(> ?i 0)) (fecha ?f) (test(< ?f anno)))
	=>
	(modify ?t(valida si)))
)



(defrule Muestra_Saldo
	(usuario(dni ?d)(pin ?p))
	(tarjeta(dni ?d)(pin ?p)(valida si)(saldo ?d))
	?c <-(cuenta(dni ?d))	
	=>
	(printout t "Tu saldo es " ?d)
	(modify ?c(estado enPantalla)))
)

(defrule Saldo_NoSuficiente
	(usuario(dni ?d)(pin ?p)(dinero ?euro))
	(tarjeta(dni ?d)(pin ?p)(valida si)(saldo 0))
	?c<-(cuenta(estado ?e))
	=>
	(printout t "No tienes saldo en tu cuenta" )
	(modify ?c(estado SinSaldo))
)	

(defrule Comprueba_Limite1
	(usuario(dni ?d)(pin ?p)(dinero ?euro))
	?t<-(tarjeta(dni ?d)(pin ?p)(valida si)(limite ?lim))
	(test(> ?euro ?lim))
	?c<-(cuenta(estado ?e))
	=>
	(printout t "No puedes sacar " ?euro " euros, has exceido el limite permitido")
	(modify ?t(valida no))
	(modify ?c(estado SuperaLimite))
)

(defrule Comprueba_Limite2 
	(usuario(dni ?d)(pin ?p)(dinero ?euro))
	t?<-(tarjeta(dni ?d)(pin ?p)(valida si)(saldo ?s))
	(test(< ?s ?euro)
	?c<-(cuenta(estado ?e))
	=>
	(printout t "No puedes sacar " ?euro " tu saldo es de " ?s " euros" )
	(modify ?t(valida no))
	(modify ?c(estado SuperaLimite))
)

(defrule Entrega_Dinero
		(declare (salience 100))
	(usuario(dni ?d)(pin ?p)(dinero ?euro))
	?t<-(tarjeta(dni ?d)(pin ?p)(valida si)(saldo ?s)(limite ?lim)
	?c<-(cuenta(estado ?e))	
	(test(< ?euro ?s))
	(test(< ?euro ?lim))
	=>
	(modify ?t(saldo (diferencia ?s ?euro)))
	(modify ?c(estado DineroEntregado) )
)	













	  
	



