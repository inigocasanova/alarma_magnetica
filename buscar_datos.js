	//Creo que buscamos el elemento donde vamos a poner la tabla.
	const listaDeActividad = document.querySelector("#lista-actividad");

	//Función para generar la tabla.
	const generarTabla = (datos) => {
		//Iteramos en los eventos
		datos.eventos.forEach((evento) => {
			//Creamos unos divs
			const nuevoDivDeLinea = document.createElement('tr');

			//Definimos algo de html que ponerle a nuestro nuevo div.
			const movimientoHTML = `
			<td>${evento.tipo}</td>
			<td>${evento.fecha}</td>
			<td>${evento.hora}</td>
			`;
		
			//Le metemos el html definido a listaDeActividad.
			nuevoDivDeLinea.innerHTML = movimientoHTML;
			//Agregar el div al div de las listas.
			listaDeActividad.appendChild(nuevoDivDeLinea);
		});
	};

		
	//Agarramos los datos del documento.
	fetch("logs.json")
	.then(response => response.json())
	.then(datos => generarTabla(datos));
