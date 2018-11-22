(watch facts)
(watch rules)
(watch agenda)

(clear)
(reset)

(defglobal
    ?*anio* = 2018
)

(deftemplate usuario
    (slot dni (type INTEGER))
    (slot pin (type INTEGER))
    (slot cantidad (type FLOAT))
)

(deftemplate tarjeta
    (slot dni (type INTEGER))
    (slot pin (type INTEGER))
    (slot n_intentos (type INTEGER) (default 3))
    (slot limite_dinero (type FLOAT) (default 500.0))
    (slot anio_exp (type INTEGER) (default ?*anio*))
    (slot tarjeta_valid (allowed-values Si No))
)

(deftemplate cuenta
    (slot dni (type INTEGER))
    (slot saldo (type FLOAT))
    (slot estado (allowed-values EnPantalla DineroEntregado Inicial SuperaLimite SinSaldo)
                 (default Inicial)
    )
)

(deffacts facts_on_init
    (usuario (dni 123456)
             (pin 1212)
             (cantidad 300000.0)
    )
    (usuario (dni 456456)
             (pin 4545)
             (cantidad 200.0)
    )
    (usuario (dni 123456)
             (pin 4545)
             (cantidad 3000.0)
    )
    (tarjeta (dni 123456)
             (pin 1212)
             (n_intentos 3)
             (limite_dinero 500.0)
             (anio_exp 2020)
    )
    (tarjeta (dni 456456)
             (pin 4545)
             (n_intentos 3)
             (limite_dinero 500.0)
             (anio_exp 2020)
    )
    (tarjeta (dni 000111)
             (pin 0011)
             (n_intentos 0)
             (limite_dinero 500.0)
             (anio_exp 2020)
    )
    (cuenta (dni 123456)
            (saldo 5000.0)
    )
    (cuenta (dni 456456)
            (saldo 1000.0)
    )
    (cuenta (dni 000111)
            (saldo 30000.0)
    )
)
(reset)

(defrule Supera_Intentos
    (declare (salience 100))
    (usuario (dni ?d))
    (tarjeta (dni ?d) (n_intentos 0))
    =>
    (printout t crlf)
    (printout t "---------------------------------------------------------------------" crlf)
    (printout t "Usuario con DNI: " ?d " ha excedido el numero de intentos permitidos." crlf)
    (printout t "---------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(defrule Pin_Invalido
    (declare (salience 99))
    ?u <- (usuario (dni ?d) (pin ?pinUser))
    ?t <- (tarjeta (dni ?d) (pin ?pinTarjeta) (n_intentos ?intentos))
    (test (<> ?pinUser ?pinTarjeta))
    (test (> ?intentos 0))
    =>
    (modify ?t (n_intentos (- ?intentos 1)))
    (retract ?u)
    (printout t crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t "Usuario con DNI: " ?d " ha introducido un pin incorrecto." crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(defrule Valida_Tarjeta
    (declare (salience 98))
    (usuario (dni ?d) (pin ?pin))
    (tarjeta (dni ?d) (pin ?pin) (n_intentos ?intentos) (anio_exp ?anioExp))
    ;(tarjeta (dni ?d) (pin ?pinTarjeta&~?pinUser) (n_intentos ?intentos) (anio_exp ?anioExp))
    (test (> ?intentos 0))
    (test (<= ?*anio* ?anioExp))
    (not (exists (tarjeta_valida ?d ?pin)))
    =>
    (assert (tarjeta_valida ?d ?pin))
    (printout t crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t "La tarjeta con DNI: " ?d " se ha  validado." crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(defrule Muestra_Saldo
    (declare (salience 97))
    (tarjeta_valida ?dni ?pin)
    (usuario (dni ?dni) (pin ?pin))
    (tarjeta (dni ?dni) (pin ?pin))
    ?c <- (cuenta  (dni ?dni) (saldo ?saldo) (estado ?estado))
    (test (= (str-compare ?estado Inicial) 0))
    =>
    (modify ?c (estado EnPantalla))
    (printout t crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t "El saldo de la cuenta es: " ?saldo crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(defrule Comprueba_Limite1
    (declare (salience 96))
    (tarjeta_valida ?dni ?pin)
    (usuario (dni ?dni) (pin ?pin) (cantidad ?cantidad))
    (tarjeta (dni ?dni) (pin ?pin))
    ?c <- (cuenta  (dni ?dni) (saldo ?saldo) (estado ?estado))
    (test (< ?saldo ?cantidad))
    (not (exists (saldo_insuficiente ?dni ?pin ?ident)))
    (test (<> (str-compare ?estado DineroEntregado) 0))
    =>
    (assert (saldo_insuficiente ?dni ?pin cuenta))
    (modify ?c (estado SuperaLimite))
)

(defrule Comprueba_Limite2
    (declare (salience 95))
    (tarjeta_valida ?dni ?pin)
    (usuario (dni ?dni) (pin ?pin) (cantidad ?cantidad))
    (tarjeta (dni ?dni) (pin ?pin) (limite_dinero ?limite))
    ?c <- (cuenta  (dni ?dni) (saldo ?saldo) (estado ?estado))
    (test (< ?limite ?cantidad))
    (not (exists (saldo_insuficiente ?dni ?pin ?ident)))
    (test (<> (str-compare ?estado DineroEntregado) 0))
    =>
    (assert (saldo_insuficiente ?dni ?pin tarjeta))
    (modify ?c (estado SuperaLimite))
)

(defrule Saldo_NoSuficiente
    (declare (salience 94))
    (cuenta (estado SuperaLimite))
    (saldo_insuficiente ?dni ?pin ?ident)
    =>
    (printout t crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t "El saldo de la "?ident" es insuficiente para la cantidad exigida." crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(defrule Entrega_Dinero
    (declare (salience 93))
    (tarjeta_valida ?dni ?pin)
    ?p <- (usuario (dni ?dni) (pin ?pin) (cantidad ?cantidad))
    ?t <- (tarjeta (dni ?dni) (pin ?pin) (limite_dinero ?limite))
    ?c <- (cuenta  (dni ?dni) (saldo ?saldo) (estado ?estado))
    (not (exists (saldo_insuficiente ?dni ?pin ?ident)))
    (test (<> (str-compare ?estado DineroEntregado) 0))
    =>
    (modify ?t (limite_dinero (- ?limite ?cantidad) ))
    (modify ?c (saldo (- ?saldo ?cantidad)) (estado DineroEntregado))
    (printout t crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t "El nuevo saldo es: " (- ?saldo ?cantidad) " (" ?saldo " - " ?cantidad ")." crlf)
    (printout t "--------------------------------------------------------------------" crlf)
    (printout t crlf)
)

(run)











