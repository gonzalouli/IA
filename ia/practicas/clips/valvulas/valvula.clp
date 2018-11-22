(watch facts)
(watch rules)

(clear)
(reset)

(deftemplate valvula
    (slot nombre)
    (slot estado (allowed-values abierta cerrada) (default cerrada))
    (slot presion (type FLOAT) (default 0.0))
    (slot temp_interna (type FLOAT) (default 0.0))
    (slot temp_externa (type FLOAT) (default 0.0))
)

(deffacts facts_on_init
    (valvula (nombre Entrada)
             (presion 1.0)
             (temp_interna 101.0)
             (temp_externa 35.0)
    )
    (valvula (nombre Salida)
             (presion 5.0)
             (temp_interna 101.0)
             (temp_externa 155.0)
    )
    (valvula (nombre Pasillo1)
             (estado cerrada)
             (temp_interna 101.0)
             (temp_externa 155.0)
    )
)

(reset)

(deffunction refrigerar (?presion ?tempInterna)
    (while (> ?tempInterna 35)
        (bind ?presion (+ ?presion 1))
        (bind ?tempInterna (- ?tempInterna 5))
    )
    (return (create$ ?presion ?tempInterna))
)

(deffunction refrigerar2 (?temp1 ?temp2)
    (if (> ?temp2 ?temp1) then
        (bind ?temp2 (- ?temp2 ?temp1))
    )
    (return ?temp2)
)

(defrule R1_Presion5
    ?valvula <- (valvula (estado abierta) (presion 5.0))
    =>
    (modify ?valvula (estado cerrada) (presion 0.0))
)

(defrule R2_DecrementaTempInterna
    ?valvula <- (valvula (estado cerrada) (presion ?presion) (temp_interna ?tempInterna))
    (test (< ?presion 10))
    (test (> ?tempInterna 35))
    =>
    ;(printout t "Dime el resultado => " (refrigerar ?presion ?tempInterna) crlf)
    (modify ?valvula (estado abierta) (presion (nth$ 1 (refrigerar ?presion ?tempInterna))))
    (printout t "Nueva presion => " (nth$ 1 (refrigerar ?presion ?tempInterna)) crlf)
)

(defrule R3_ValvulasTemp
    ?valvula1 <- (valvula (nombre ?nombreValv1) (estado cerrada) (temp_interna ?tempInterna1) (temp_externa ?tempExterna))
    ?valvula2 <- (valvula (nombre ?nombreValv2&~?nombreValv1) (estado cerrada) (temp_interna ?tempInterna2) (temp_externa ?tempExterna))
    (test (< ?tempInterna2 ?tempExterna))
    =>
    (modify ?valvula1 (estado abierta))
    (modify ?valvula2 (estado abierta) (temp_externa (refrigerar2 ?tempInterna2 ?tempExterna)))
    (printout t "Nueva temperatura externa => " (refrigerar2 ?tempInterna2 ?tempExterna) crlf)
)

(run)
