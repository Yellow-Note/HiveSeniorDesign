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
  setup() {
    const center = { lat: 41.1544, lng: -105.3745 }

    return { center }
  },
})
</script>