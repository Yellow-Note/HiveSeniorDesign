<template>

  <GoogleMap
    api-key="API-KEY!!!"
    style="width: 100%; height: 500px"
    :center="center"
    :zoom="15"
    >
      <Marker :options="{ position: center }" />
    </GoogleMap>

</template>

<script>
import { defineComponent } from 'vue'
import { GoogleMap, Marker } from 'vue3-google-map'

export default defineComponent({
  components: { GoogleMap, Marker },
  props: {
    lng: {
      default: 0
    },
    lat: {
      default: 0
    }
  },
  computed: {
    center: function () {
        return { lat: this.lat, lng: this.lng }
    }
  },
  methods: {
    update() {
    this.center = { lat: parseFloat(this.lat), lng: parseFloat(this.lng) }
    }
  }
})
</script>