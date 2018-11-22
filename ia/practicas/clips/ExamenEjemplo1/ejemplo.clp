(watch facts)
(watch rules)
(watch agenda)

(clear)
(reset)

(deftemplate Productos
    (slot id)
    (slot nombre)
    (slot pasillo)
    (slot stock)
    (slot precio)
)
(deftemplate Pedidos
    (slot id_cliente)
    (slot id_producto)
    (slot unidades)
)
(deftemplate Carro
    (slot id_cliente)
    (slot pasillo (default 1))
    (slot factura (default 0))
    (slot num_productos (default 0))
)

(deffunction decrementa (?arg1 ?arg2)
    (- ?arg1 ?arg2)
)

(defrule R1_asignarCarro
    ?nc <- (nuevo_cliente ?ic)
    (not (Carro (id_cliente ?ic)))
    =>
    (assert (Carro (id_cliente ?ic)
                   (pasillo 1)
                   (factura 0)
                   (num_productos 0)
            )
    )
    (retract ?nc)
)

(defrule R3_comprar
    (Carro (id_cliente ?id) (pasillo ?pp) (factura ?fc) (num_productos ?np))
    ?fp <- (Pedidos (id_cliente ?id) (producto ?ip) (unidades ?u))
    ?fpr <- (Productos (id ?ip) (pasillo ?pp) (stock ?sp) (precio ?pre))
    (test (>= ?sp ?u))
    =>
    (retract ?fp)
    (modify ?fpr (stock (- ?sp ?u)))
    (modify ?fc (factura (+ ?fc (* ?u ?pre)))
                (num_productos (+ ?np ?u))
    )
)
