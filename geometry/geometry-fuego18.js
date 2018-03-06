const Stripe = require('../light-programs/stripe')

/**
 * Geometry for the mate: 10 stripes
 *                (0, 2.5)      (0, 5)     (0, W)
 * (0, 0) * --------- * --------- * -------- * (W, 0)
 * (0, 0) *    *    *    *    *    *    *    * (W, 0)
 *        |    |    |    |    |    |    |    |
 *        |    |    |    |    |    |    |    |
 *        |    |    |    |    |    |    |    |
 *        |    |    |    |    |    |    |    |
 *        |    |    |    |    |    |    |    |
 * (0, H) *    *    *    *    *    *    *    * (W, H)
 *
 */
const scale = 0.1;

const PORTION = 200 * scale
const WIDTH = 7 * PORTION
const HEIGHT = PORTION * 4
const HALF_HEIGHT = HEIGHT / 2
const HALF_WIDTH = WIDTH / 2

/**
 * Amount of leds on each part
 */
const LEDS_LONG = 150
const HALF_LEDS = LEDS_LONG / 2;

// El orden de los segmentos es clave. Replica cómo vamos a conectar las luces y el orden natural de esos 600 leds

module.exports = [
  // Columnas
  new Stripe(PORTION * 0, 0, PORTION * 0, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 1, 0, PORTION * 1, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 2, 0, PORTION * 2, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 3, 0, PORTION * 3, HEIGHT, LEDS_LONG),

  new Stripe(PORTION * 4, 0, PORTION * 4, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 5, 0, PORTION * 5, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 6, 0, PORTION * 6, HEIGHT, LEDS_LONG),
  new Stripe(PORTION * 7, 0, PORTION * 7, HEIGHT, LEDS_LONG),

  // Tapa
  new Stripe(PORTION * 0, 0, PORTION * 2.5, 0, LEDS_LONG),
  new Stripe(PORTION * 2.5, 0, PORTION * 5, 0, LEDS_LONG),
  // new Stripe(PORTION * 5, 0, PORTION * 7, 0, LEDS_LONG),
]

