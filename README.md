Oh shit, here we go again...

R==15/07/25 --> cree lo basico, terminal y guardar los "comandos"

W==18/07/25 --> Empecé con el bonus del pipex para concatenar varios comandos, la lógica está puesta,
                faltaría únicamente completar las funciones, pero aún estoy viendo como pq no me acuerdo.

W==24/09/2025 --> Fui haciendo lo de los built in y escribí un par de cosas y código en la carpeta

W & R== 07/10/2025 --> Encotramos que el PWD y el ECHO (que hizo Rodri con lo de las comillas por arreglar) 
                        ya se ejecutan por estar en el PATH gracias al Pipex, pero hay que guardar el environment 
                        en un char por si lo borran, subir el LVLSHELL y además hay que verificar si los builts-in
                        existen (si no han borrado el env o el PATH), y ahí crearlos, eso puede ser fuera del PIPEX.

W== 07/10/2025 part 2 --> Se creó el built de pwd, de cd y el de env, junto al de exit, falta comprobar como mejorar el 
                        funcionamiento por que en mi caso uso envp y hace falta env.

W== 25/11/2025 --> El built-in de unset está casi listo, falta programar la actualización de ambos env, tanto g_env como env.

W== 20/12/2025 --> El bult-in de unset y de export está listo, también modifiqué las funciones para que solo se actualice el
                    g_env, sin tocar el original, para eso tenemos el bash real, o eso entiendo, por lo que ya debería de funcionar
                    sin problema, compila y de momento sirve.
