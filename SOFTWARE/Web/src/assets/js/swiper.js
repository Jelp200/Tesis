// swiper.js
var swiperPortfolio = new Swiper(".portfolioSwiper", {
    slidesPerView: 3,
    spaceBetween: 30,
    loop: true,
    autoplay: {
        delay: 2500,
        disableOnInteraction: false,
    },
    breakpoints: {
        1200: {
            slidesPerView: 3,
            spaceBetween: 30,
        },
        900: {
            slidesPerView: 2,
            spaceBetween: 30,
        },
        500: {
            slidesPerView: 1,
            spaceBetween: 10,
        }
    },
});

var swiperSlider = new Swiper(".slider", {
    direction: "vertical",
    autoplay: {
        delay: 2500,
        disableOnInteraction: false,
    },
    loop: true,
    speed: 3000,
    parallax: true,
    mousewheel: true,
    navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
    },
    pagination: {
        el: '.swiper-pagination',
        clickable: true,
    }
});

var swiperPortfolio = new Swiper(".testimonialSwiper", {
    slidesPerView: 2,
    spaceBetween: 20,
    loop: true,
    autoplay: {
        delay: 4000,
        disableOnInteraction: false,
    },
    breakpoints: {
        1200: {
            slidesPerView: 2,
            spaceBetween: 20,
        },
        900: {
            slidesPerView: 1,
            spaceBetween: 20,
        },
        500: {
            slidesPerView: 1,
            spaceBetween: 10,
        }
    },
});

var swiperPortfolio = new Swiper(".brandSwiper", {
    slidesPerView: 5,
    spaceBetween: 20,
    loop: true,
    autoplay: {
        delay: 3000,
        disableOnInteraction: false,
    },
    breakpoints: {
        1200: {
            slidesPerView: 5,
            spaceBetween: 20,
        },
        900: {
            slidesPerView: 3,
            spaceBetween: 20,
        },
        500: {
            slidesPerView: 3,
            spaceBetween: 10,
        }
    },
});

var swiperPortfolio = new Swiper(".BlogSwiper", {
    slidesPerView: 3,
    spaceBetween: 20,
    loop: true,
    autoplay: {
        delay: 4000,
        disableOnInteraction: false,
    },
    breakpoints: {
        1200: {
            slidesPerView: 3,
            spaceBetween: 20,
        },
        900: {
            slidesPerView: 2,
            spaceBetween: 20,
        },
        500: {
            slidesPerView: 1,
            spaceBetween: 10,
        }
    },
});