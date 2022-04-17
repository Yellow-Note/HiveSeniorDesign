<template>
  <div class="home">
    <div class="row justify-content-center">
      <div class='col-10'>
        <img class="img-fluid" :src="image" alt="Side Bar Picture">

        <div class="mb-3">
          <label for="formFile" class="form-label">Import .MOV File</label>
          <input class="form-control" type="file" @change="importFile($event)">
          <div class="form-text">Select one ".MOV" file to import at a time.</div>
        </div>
        <div class="d-grid gap-2">
          <button class="btn btn-primary" type="button" @click="changeImage" >Change Image</button>
        </div>
      <!--<file-selector v-model="files">
        <dropzone v-slot
      </file-selector> -->
    </div>
  </div>
  </div>
</template>

<script>
const { ipcRenderer } = require('electron')
window.ipcRenderer = ipcRenderer

export default {
  name: 'HomeView',
  components: {
    
  },
  data() {
    return {
      backgroundImage: "./assets/background/Burning.webm",
      images: ["@/assets/logo.png", "@/assets/images.png"],
      image: require("@/assets/drawing3.svg")
    }
  },
  methods: {
    importFile(event){
      var result = 'none'
      if(event.target.files.length > 0) {
        var filePath = event.target.files[0].path
        /* eslint-disable no-unused-vars */
        
      }
      result = ipcRenderer.invoke('importfile', filePath).then(this.callAlert(result))

    },
    callAlert(message){
      alert(message)
    },
    changeImage() {
      this.image = require(this.images[1])
    }
  }
}
</script>
