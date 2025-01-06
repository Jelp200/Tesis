// faq.js
let Quest = document.querySelectorAll('.question');
let pera = document.querySelectorAll('.faq-pera');
let QnsHead = document.querySelectorAll('.qns_icon');

Quest.forEach((drop, index) => {
    drop.addEventListener('click', () => {
        const answer = drop.lastElementChild;

        // Si ya está abierta, la cerramos y salimos de la función
        if (answer.classList.contains('showQuestion')) {
            answer.classList.remove('showQuestion');
            QnsHead[index].classList.remove('active_ans');
            return;
        }

        // Cerrar todas las respuestas antes de abrir la seleccionada
        pera.forEach(peragraph => {
            peragraph.classList.remove('showQuestion');
        });
        QnsHead.forEach(icon => {
            icon.classList.remove('active_ans');
        });

        // Abrir la respuesta seleccionada
        answer.classList.toggle('showQuestion');
        QnsHead[index].classList.toggle('active_ans');
    });
});

