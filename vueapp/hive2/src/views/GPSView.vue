<template>
    <div>
        <div class="container-fluid" >
            <div class="row">
                <div class="col-8">
                    <div class="map-responsive">
                        <GoogleMap class="map-responsive-googlemap" 
                        :lat="this.currentlat" :lng="this.currentlng"></GoogleMap>
                    </div>
                </div>
                <div class="col-4">
                    <div class="list-group">
                        <div v-for="video in mediaStore.videos" :key="video.timestamp">
                            <div v-for="image in video.alertedImages" :key="image.imageName">
                                <div class="list-group-item list-group-item-action" @click="changePin(image.gps, image.url)">Video: {{video.timestamp}} Image: {{image.imageName}}</div>
                            </div>
                        </div>
                        <div>
                        </div>
                        <!--
                    <picture :key="currImageURL">
                        <source :src="currImageURL">
                    </picture>
                    -->
                    <div :key="currentImage">
                        <img :src="currentImage" width="460">
                    </div>
                    </div>
                </div>
            </div>
        </div>    
    </div>
</template>
<script>

//import { array } from 'yargs'
import GoogleMap from '../components/GoogleMap.vue'
import { usemediaStore } from '@/store/mediaStore'
import {ref} from 'vue'

export default {
    setup() {
        let mediaStore = usemediaStore()
        let currentImage = ref(require("@/assets/drawing3.svg"))
        let currentlat = ref(41.31685383399975)
        let currentlng = ref(-105.56706454495476)
        return { mediaStore, currentImage , currentlat, currentlng}
    },
    components: {
        GoogleMap
    }, 
    computed: {
      currImageURL: function() {
          
          return require(this.currentImage)
      }
    },
    
    methods: {
        changePin(data, imageURL){
            this.currentlat = data.lat
            this.currentlng = data.lng
            this.currentImage = imageURL
            return
        }
    }
    
}


</script>


<style scope>
.map-responsive{
    overflow:hidden;
    padding-bottom:67%;
    position:relative;
    height:0;
}
.map-responsive-googlemap{
    left:5%; 
    top:0;
    height:100%;
    width:100%;
    position:absolute;
}
</style>